#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <thread>
#include <vector>
#include "process.h"

void
try_ptrace(enum __ptrace_request request, pid_t pid, void* addr, void* data)
{
  std::vector<char> buffer(1024, 0x00);
  errno = 0;
  
  if (ptrace(request, pid, addr, data)) {
    fprintf(stderr,
            "errno(%d) - %s\n",
            errno,
            strerror_r(errno, buffer.data(), buffer.size()));
    exit(EXIT_FAILURE);
  }
}

bool
try_peek(pid_t pid, void* addr, uint64_t& val)
{

  if ((uint64_t)addr % 8) {
    return false;
  }

  std::vector<char> buffer(1024, 0x00);
  errno = 0;
  auto rez = ptrace(PTRACE_PEEKDATA, pid, addr, 0);
  if (errno) {
    fprintf(stderr,
            "errno(%d) - %s - %lX - %p\n",
            errno,
            strerror_r(errno, buffer.data(), buffer.size()),
            rez,
            addr);
    return false;
  }
  val = rez;
  return true;
}

std::map<void*, uint64_t>
dump_stack(pid_t pid, uint64_t rbp, uint64_t rsp)
{
  if (!(rbp && rsp)) {
    return {};
  }

  std::map<void*, uint64_t> vals;
  while (rbp >= rsp) {
    uint64_t val{ 0 };
    if (try_peek(pid, (void*)rbp, val)) {
      vals[(void*)rbp] = val;
    }
    rbp -= 8;
  }
  return vals;
}

std::string get_process_name(pid_t pid)
{
  std::ifstream file("/proc/" + std::to_string(pid) + "/cmdline", std::ios::binary);
  std::streambuf* raw_buffer = file.rdbuf();

  char block[255];
  raw_buffer->sgetn(block, 255);
  return std::string(block);
}

void*
get_stack_bottom(pid_t pid)
{
  std::ifstream in("/proc/" + std::to_string(pid) + "/maps");
  std::string line;
  while (std::getline(in, line)) {
    if (line.find("[stack]") != std::string::npos) {
      auto base =
        line.substr(line.find_first_of("-") + 1, line.find_first_of(" "));
      return (void*)std::strtoull(base.c_str(), nullptr, 16);
    }
  }
  return nullptr;
}



int
main(int argc, char* argv[])
{
  std::vector<char> buffer(0x1000, 0x0);

  if (argc != 2) {
    fprintf(stderr, "%s pid_of_process or\n", argv[0]);
    fprintf(stderr, "%s `echo $$`\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  const pid_t pid = strtoul(argv[1], nullptr, 10);
  if (errno) {
    fprintf(stderr,
            "errno(%d) - %s\n",
            errno,
            strerror_r(errno, buffer.data(), buffer.size()));
    exit(EXIT_FAILURE);
  }

  std::string proc_name = get_process_name(pid);
  std::cout << "Process name is " << proc_name << '\n';
  try_ptrace(PTRACE_ATTACH, pid, 0, 0);

  int status{ -1 };
  auto wait_res = waitpid(pid, &status, WUNTRACED);

  if (wait_res != pid || !WIFSTOPPED(status)) {
    fprintf(stderr, "Not ok!\n");
    exit(EXIT_FAILURE);
  }

  struct user_regs_struct regs = {};
  try_ptrace(PTRACE_GETREGS, pid, nullptr, &regs);
  printf(
    "FramePointer(%#llX), StackPointer(%#llX), InstructionPointer(%#llX)\n",
    regs.rbp,
    regs.rsp,
    regs.rip);

  // Dump Stack
  // We know that the stack grows downwards starting from RBP
  // *(RBP) is the old RBP
  // *(RBP + 8) is the return address
  // *(RBP + 16) are the function args in order

  auto vals = std::map<void*, uint64_t>();
  uint64_t start = regs.rbp;
  // Frame pointer has been optimised - read stack base
  if (!start || start % 8) {
    start = (uint64_t)get_stack_bottom(pid);
  }

  vals = dump_stack(pid, start, regs.rsp);
  for (auto&& [k, v] : vals) {
    printf("%p => %lX\n", k, v);
  }

  // Let's fuck up the stack
  //for (auto&& [k, _] : vals) {
    //try_ptrace(PTRACE_POKEDATA, pid, k, 0);
  //}
   auto *test = new Process(pid);
  while (false) {

    printf("Stepping\n");
    try_ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
    status = -1;
    wait_res = waitpid(pid, &status, WUNTRACED);

    if (wait_res != pid || !WIFSTOPPED(status) || !WIFSIGNALED(status)) {
      break;
    }

    try_ptrace(PTRACE_GETREGS, pid, nullptr, &regs);
    printf(
      "FramePointer(%#llX), StackPointer(%#llX), InstructionPointer(%#llX)\n",
      regs.rbp,
      regs.rsp,
      regs.rip);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
  }

  
  buffer.clear();

  return EXIT_SUCCESS;
}
