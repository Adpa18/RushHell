//
// Created by nicolas-constanty on 03/12/16.
//

#ifndef TEST_FSA_MACHINE_H
#define TEST_FSA_MACHINE_H

#ifndef STATE_MAX
#define STATE_MAX   8
#endif //!STATE_MAX

#ifndef EDGE_MAX
#define EDGE_MAX    8
#endif //!EDGE_MAX

enum eState
{
    S0 = 0,
    S1,
    S2,
    S3,
    S4,
    S5,
    S6,
    S7,
    STATE_ERROR
};

enum eAction
{
    MA,
    HR,
    ACTION_ERROR
};



extern eState gStateTable[STATE_MAX][EDGE_MAX];
extern eAction gActionTable[STATE_MAX][EDGE_MAX];

#endif //TEST_FSA_MACHINE_H
