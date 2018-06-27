#ifndef RFM69_GP_H
#define RFM69_GP_H

#include <Arduino.h>
#include <RFM69.h>
#include "RFM69_CONF.h"

class RFM69GP : RFM69
{
    public:
         bool initialize(RFM69Config config);


    protected:

    private:
    
};

#endif