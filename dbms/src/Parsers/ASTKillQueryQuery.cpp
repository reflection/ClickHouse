#include <Parsers/ASTKillQueryQuery.h>

namespace DB
{

String ASTKillQueryQuery::getID(char delim) const
{
    return String("KillQueryQuery") + delim + (where_expression ? where_expression->getID() : "") + delim + String(sync ? "SYNC" : "ASYNC");
}

void ASTKillQueryQuery::formatQueryImpl(const FormatSettings & settings, FormatState & state, FormatStateStacked frame) const
{
    settings.ostr << (settings.hilite ? hilite_keyword : "") << "KILL QUERY";

    formatOnCluster(settings);
    settings.ostr << " WHERE " << (settings.hilite ? hilite_none : "");

    if (where_expression)
        where_expression->formatImpl(settings, state, frame);

    settings.ostr << " " << (settings.hilite ? hilite_keyword : "") << (test ? "TEST" : (sync ? "SYNC" : "ASYNC")) << (settings.hilite ? hilite_none : "");
}

}
