#include "gtghostplugin.h"

#include <QtQml/QtQml>

#include "gghostglobal.h"
#include "gghostnode_p.h"
#include "gghosttree_p.h"
#include "gghostdata_p.h"
#include "gcompositenode_p.h"
#include "gdecoratornode_p.h"
#include "gleafnode_p.h"
#include "gsequencenode_p.h"
#include "gselectornode_p.h"
#include "gparallelnode_p.h"
#include "gprioritysequencenode_p.h"
#include "gpriorityselectornode_p.h"
#include "grandomsequencenode_p.h"
#include "grandomselectornode_p.h"
#include "ginverternode_p.h"
#include "grepeaternode_p.h"
#include "grepeatuntilsuccessnode_p.h"
#include "grepeatuntilfailurenode_p.h"
#include "gforcesuccessnode_p.h"
#include "gforcefailurenode_p.h"
#include "gactionnode_p.h"
#include "gconditionnode_p.h"
#include "gfreezenode_p.h"

#include "gghostinspector_p.h"

void GtGhostPlugin::registerTypes(const char *uri)
{
    // @uri GtGhost

    Q_ASSERT(qstrcmp(uri, "GtGhost") == 0);

    qRegisterMetaType<Ghost::Status>("Ghost::Status");

    qmlRegisterUncreatableType<Ghost>(uri, 1, 0, "Ghost", "Ghost is an abstract class.");
    qmlRegisterUncreatableType<GGhostNode>(uri, 1, 0, "GhostNode", "GhostNode is an abstract class.");
    qmlRegisterUncreatableType<GGhostData>(uri, 1, 0, "GhostData", "GhostData is an abstract class.");
    qmlRegisterUncreatableType<GCompositeNode>(uri, 1, 0, "CompositeNode", "CompositeNode is an abstract class.");
    qmlRegisterUncreatableType<GDecoratorNode>(uri, 1, 0, "DecoratorNode", "DecoratorNode is an abstract class.");
    qmlRegisterUncreatableType<GLeafNode>(uri, 1, 0, "LeafNode", "LeafNode is an abstract class.");

    qmlRegisterType<GGhostTree>(uri, 1, 0, "GhostTree");

    qmlRegisterType<GSequenceNode>(uri, 1, 0, "SequenceNode");
    qmlRegisterType<GSelectorNode>(uri, 1, 0, "SelectorNode");
    qmlRegisterType<GParallelNode>(uri, 1, 0, "ParallelNode");
    qmlRegisterType<GPrioritySequenceNode>(uri, 1, 0, "PrioritySequenceNode");
    qmlRegisterType<GPrioritySelectorNode>(uri, 1, 0, "PrioritySelectorNode");
    qmlRegisterType<GRandomSequenceNode>(uri, 1, 0, "RandomSequenceNode");
    qmlRegisterType<GRandomSelectorNode>(uri, 1, 0, "RandomSelectorNode");

    qmlRegisterType<GInverterNode>(uri, 1, 0, "InverterNode");
    qmlRegisterType<GRepeaterNode>(uri, 1, 0, "RepeaterNode");
    qmlRegisterType<GRepeatUntilSuccessNode>(uri, 1, 0, "RepeatUntilSuccessNode");
    qmlRegisterType<GRepeatUntilFailureNode>(uri, 1, 0, "RepeatUntilFailureNode");
    qmlRegisterType<GForceSuccessNode>(uri, 1, 0, "ForceSuccessNode");
    qmlRegisterType<GForceFailureNode>(uri, 1, 0, "ForceFailureNode");

    qmlRegisterType<GActionNode>(uri, 1, 0, "ActionNode");
    qmlRegisterType<GConditionNode>(uri, 1, 0, "ConditionNode");
    qmlRegisterType<GFreezeNode>(uri, 1, 0, "FreezeNode");

    qmlRegisterType<GGhostInspector>(uri, 1, 0, "GhostInspector");
}


