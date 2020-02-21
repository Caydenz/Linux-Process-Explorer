#pragma once

class Process {
private:
    int pid;
public:
    explicit Process(int pid);

    virtual ~Process();

    int getPid() const;

    void setPid(int pid);


};