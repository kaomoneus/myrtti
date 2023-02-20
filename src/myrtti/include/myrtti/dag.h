#ifndef MYRTTI_DAG_H
#define MYRTTI_DAG_H

namespace myrtti {

    template<typename NodeT>
    struct DAG {
        template<typename ForkNodeT>
        DAG fork();
        // TODO: path
        // template paremter: resolver class (early, lazy)
    };

} // namespace myrtti

#endif
