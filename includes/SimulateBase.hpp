#pragma once

class SimulateBase {
   protected:
    static const int N = 10000;

   public:
    virtual void run() = 0;
};