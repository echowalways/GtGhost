#include "gtghostplugin.h"

#include <QtQml/QtQml>

#include "gghostnode.h"
#include "gghosttree.h"
#include "gghostitem.h"

#include "gcompositeitem.h"
#include "glinearsequenceitem.h"
#include "glinearselectoritem.h"
#include "gweightsequenceitem.h"
#include "gweightselectoritem.h"
#include "grandomsequenceitem.h"
#include "grandomselectoritem.h"

#include "gdecoratoritem.h"
#include "ginverteritem.h"
#include "grepeateritem.h"
#include "grepeatuntilsuccessitem.h"
#include "grepeatuntilfailureitem.h"
#include "galwayssuccessitem.h"
#include "galwaysfailureitem.h"

#include "gconditionitem.h"

#include "gactionitem.h"
#include "gidleactionitem.h"

#if !defined(GT_NO_GHOSTVIEW)
#include "gghostview.h"
#include "gghostviewitem.h"
#endif

#if defined(GT_GHOST_UNITTEST)
#include "gghostunittest.h"
#endif

void GtGhostPlugin::registerTypes(const char *uri)
{
    // @uri GtGhost

    Q_ASSERT(qstrcmp(uri, "GtGhost") == 0);

    qRegisterMetaType<Ghost::Status>("Ghost::Status");

    qmlRegisterUncreatableType<Ghost>(uri, 1, 0, "Ghost", "Ghost is an abstract class.");

    qmlRegisterUncreatableType<GGhostNode>(uri, 1, 0, "GhostNode", "GhostNode is an abstract class.");
    qmlRegisterType<GGhostTree>(uri, 1, 0, "GhostTree");
    qmlRegisterUncreatableType<GGhostItem>(uri, 1, 0, "GhostItem", "GhostItem is an abstract class.");

    qmlRegisterUncreatableType<GCompositeItem>(uri, 1, 0, "CompositeItem", "CompositeItem is an abstract class.");
    qmlRegisterType<GLinearSequenceItem>(uri, 1, 0, "LinearSequenceItem");
    qmlRegisterType<GLinearSelectorItem>(uri, 1, 0, "LinearSelectorItem");
    qmlRegisterType<GWeightSequenceItem>(uri, 1, 0, "WeightSequenceItem");
    qmlRegisterType<GWeightSelectorItem>(uri, 1, 0, "WeightSelectorItem");
    qmlRegisterType<GRandomSequenceItem>(uri, 1, 0, "RandomSequenceItem");
    qmlRegisterType<GRandomSelectorItem>(uri, 1, 0, "RandomSelectorItem");
    qmlRegisterType<GLinearSequenceItem>(uri, 1, 0, "SequenceItem");
    qmlRegisterType<GLinearSelectorItem>(uri, 1, 0, "SelectorItem");

    qmlRegisterUncreatableType<GDecoratorItem>(uri, 1, 0, "DecoratorItem", "DecoratorItem is an abstract class.");
    qmlRegisterType<GInverterItem>(uri, 1, 0, "InverterItem");
    qmlRegisterType<GRepeaterItem>(uri, 1, 0, "RepeaterItem");
    qmlRegisterType<GRepeatUntilSuccessItem>(uri, 1, 0, "RepeatUntilSuccessItem");
    qmlRegisterType<GRepeatUntilFailureItem>(uri, 1, 0, "RepeatUntilFailureItem");
    qmlRegisterType<GAlwaysSuccessItem>(uri, 1, 0, "AlwaysSuccessItem");
    qmlRegisterType<GAlwaysFailureItem>(uri, 1, 0, "AlwaysFailureItem");

    qmlRegisterType<GConditionItem>(uri, 1, 0, "ConditionItem");
    qmlRegisterType<GActionItem>(uri, 1, 0, "ActionItem");
    qmlRegisterType<GIdleActionItem>(uri, 1, 0, "IdleActionItem");

#if !defined(GT_NO_GHOSTVIEW)
    qmlRegisterType<GGhostView>(uri, 1, 0, "GhostView");
    qmlRegisterType<GGhostViewItem>(uri, 1, 0, "GhostViewItem");
#endif

#if defined(GT_GHOST_UNITTEST)
    qmlRegisterType<GGhostUnitTest>(uri, 1, 0, "GhostUnitTest");
#endif
}


