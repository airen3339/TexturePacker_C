#include "pvrtest.h"
#include "common/include/pvr.h"

PVRTest::PVRTest()
{
}

void PVRTest::initTestCase()
{
    m_pImg = new PVR("/Users/flavor/tmp/zw_input/植物_树1.png");
}

void PVRTest::cleanupTestCase()
{
    delete m_pImg;
}

void PVRTest::testLoad()
{
}