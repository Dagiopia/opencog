#include "AttentionUtils.h"
#include <opencog/atoms/atom_types/NameServer.h>
#include <opencog/attentionbank/types/atom_types.h>

namespace opencog
{
    void removeHebbianLinks(HandleSeq& sources)
    {
        auto it_end =
            std::remove_if(sources.begin(), sources.end(),
                    [=](const Handle& h)
                    {
                    Type type = h->get_type();
                    return nameserver().isA(type, HEBBIAN_LINK);
                    });

        sources.erase(it_end, sources.end());
    }
}
