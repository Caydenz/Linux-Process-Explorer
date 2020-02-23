#pragma once

class Process {
private:
    int pid;
public:
    explicit Process(int pid);
    Process(const Process& proc);
    Process(Process&& proc) noexcept;

    virtual ~Process();

    int getPid() const;

    void setPid(int pid);


};