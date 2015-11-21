#ifndef SIGNAL_HANDLER_H_INCLUDED
#define SIGNAL_HANDLER_H_INCLUDED

#include "signal.h"

extern bool sigint_was_hit;
extern bool sigabrt_was_hit;

class Signal_init
{
    public:
        bool sigint_was_hit;
        bool sigabrt_was_hit;

        Signal_init ( ) { sigint_was_hit = false; sigabrt_was_hit = false; };
        Signal_init ( int type_sig, __p_sig_fn_t __func ) {
            signal( type_sig, __func );
        }

        virtual~Signal_init(){
        }

};


#endif // SIGNAL_HANDLER_H_INCLUDED
