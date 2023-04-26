#include "EZ-Template/util.hpp"
#include "main.h"
#include "pistons.hpp"
#include "trajectory.hpp"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

//p want to get to 0
//d wants to get to 0 velocity

void default_constants() {
  chassis.opp_swing_p = 10.0;
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 6.2, 0.012, 67, 13);//5, 0.003, 35, 15 //Mikhael Constants 6.4, 0.006, 47, 12 //6.17, 0.015, 65, 13
  chassis.set_pid_constants(&chassis.swingPID, 6, 0, 30, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 50, 2, 220, 3, 500, 500);//100, 3, 500, 7, 500, 500 //100, 2, 500, 4, 500, 500// 70, 1, 220, 3, 500, 500
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);//100, 3, 500, 7, 500, 500
  chassis.set_exit_condition(chassis.drive_exit, 20, 40, 300, 150, 500, 500);//80, 50, 300, 150, 500, 500//20, 60, 300, 150, 500, 500
}

Trajectory path = {
        {0,0},
        {0.0158,0.0699},
        {0.0775,0.2289},
        {0.1709,0.4218},
        {0.2567,0.6071},
        {0.3395,0.7898},
        {0.4038,0.9541},
        {0.4628,1.1131},
        {0.4994,1.2495},
        {0.5218,1.3718},
        {0.5275,1.4776},
        {0.5203,1.5705},
        {0.4919,1.6419},
        {0.453,1.703},
        {0.3997,1.7497},
        {0.3375,1.7873},
        {0.2634,1.8132},
        {0.1854,1.8351},
        {0.1008,1.8503},
        {0.0165,1.863},
        {0.0808,1.8698},
        {0.1715,1.8788},
        {0.264,1.8862},
        {0.3582,1.892},
        {0.448,1.9021},
        {0.5401,1.91},
        {0.6298,1.9203},
        {0.7166,1.9335},
        {0.8037,1.9464},
        {0.8884,1.9618},
        {0.9702,1.9799},
        {1.0519,1.9982},
        {1.1314,2.0187},
        {1.2089,2.0412},
        {1.2857,2.0643},
        {1.3603,2.0897},
        {1.434,2.1161},
        {1.5067,2.1434},
        {1.5773,2.1728},
        {1.648,2.2021},
        {1.7166,2.2335},
        {1.7853,2.2648},
        {1.8524,2.2977},
        {1.9188,2.3313},
        {1.985,2.3651},
        {2.05,2.4001},
        {2.1146,2.4355},
        {2.1787,2.4714},
        {2.2424,2.5077},
        {2.3053,2.5448},
        {2.3684,2.5817},
        {2.4306,2.6195},
        {2.4929,2.6571},
        {2.5547,2.6954},
        {2.6164,2.7337},
        {2.6779,2.7721},
        {2.7393,2.8108},
        {2.8006,2.8495},
        {2.8619,2.8883},
        {2.9231,2.927},
        {2.9843,2.9657},
        {3.0456,3.0044},
        {3.1071,3.043},
        {3.1687,3.0814},
        {3.2305,3.1196},
        {3.2925,3.1576},
        {3.3549,3.1952},
        {3.4174,3.2326},
        {3.4807,3.2694},
        {3.5443,3.3058},
        {3.6083,3.3418},
        {3.6731,3.377},
        {3.7385,3.4116},
        {3.8049,3.4452},
        {3.8718,3.4783},
        {3.9402,3.5099},
        {4.0094,3.5407},
        {4.0533,3.5453},
        {4.0249,3.4818},
        {3.99,3.4167},
        {3.9553,3.3514},
        {3.9203,3.2863},
        {3.8866,3.22},
        {3.8525,3.1542},
        {3.8187,3.088},
        {3.7855,3.0211},
        {3.7532,2.9534},
        {3.7204,2.8862},
        {3.6891,2.8175},
        {3.658,2.7486},
        {3.6271,2.6795},
        {3.5972,2.6094},
        {3.5684,2.5382},
        {3.539,2.4677},
        {3.5119,2.3947},
        {3.4843,2.3224},
        {3.4573,2.2494},
        {3.4324,2.1742},
        {3.4068,2.0999},
        {3.3816,2.025},
        {3.3588,1.9478},
        {3.3349,1.8717},
        {3.3119,1.7947},
        {3.2901,1.7165},
        {3.2671,1.6395},
        {3.2457,1.5609},
        {3.2235,1.4831},
        {3.2019,1.4047},
        {3.1775,1.3292},
        {3.1565,1.2501},
        {3.1313,1.1754},
        {3.1061,1.1012},
        {3.0823,1.0295},
        {3.061,0.9607},
        {3.042,0.8949},
        {3.0242,0.8334},
        {3.0095,0.774},
        {2.9967,0.7179},
        {2.9844,0.6662},
        {2.9763,0.6156},
        {2.9659,0.5722},
        {2.9592,0.53},
        {2.9552,0.4901},
        {2.9496,0.4566},
        {2.9464,0.4256},
        {2.9426,0.4},
        {2.941,0.3771},
        {2.9401,0.3582},
        {2.9397,0.3434},
        {2.94,0.3328},
        {2.9378,0.3294},
        {2.9405,0.3258},
        {2.9422,0.3279},
        {2.9428,0.3358},
        {2.9469,0.3448},
        {2.9471,0.3625},
        {2.9539,0.3784},
        {2.9538,0.4058},
        {2.9619,0.4299},
        {2.9663,0.4622},
        {2.9732,0.497},
        {2.9811,0.5356},
        {2.9901,0.5777},
        {2.9976,0.6262},
        {3.012,0.6728},
        {3.0239,0.7268},
        {3.0388,0.7826},
        {3.0554,0.8417},
        {3.0727,0.905},
        {3.0945,0.9689},
        {3.116,1.0382},
        {3.141,1.109},
        {3.1674,1.1823},
        {3.1949,1.2547},
        {3.2173,1.3323},
        {3.2422,1.4074},
        {3.2667,1.483},
        {3.2899,1.5598},
        {3.314,1.6356},
        {3.3355,1.7141},
        {3.3618,1.7878},
        {3.3841,1.8655},
        {3.4095,1.9401},
        {3.4346,2.0151},
        {3.4611,2.0885},
        {3.486,2.1636},
        {3.5153,2.2343},
        {3.5411,2.3085},
        {3.5718,2.3778},
        {3.5998,2.4497},
        {3.63,2.5196},
        {3.6622,2.5874},
        {3.6926,2.657},
        {3.7256,2.724},
        {3.7581,2.7915},
        {3.793,2.8567},
        {3.8263,2.9233},
        {3.8619,2.9877},
        {3.8976,3.0521},
        {3.9294,3.1123},
        {3.8883,3.105},
        {3.8164,3.077},
        {3.7462,3.0472},
        {3.6762,3.0171},
        {3.6091,2.9842},
        {3.542,2.9514},
        {3.4773,2.916},
        {3.4124,2.8808},
        {3.3502,2.8431},
        {3.2868,2.8064},
        {3.2262,2.767},
        {3.1648,2.7285},
        {3.1048,2.6884},
        {3.0457,2.6475},
        {2.9862,2.607},
        {2.9281,2.5649},
        {2.8703,2.5228},
        {2.8122,2.481},
        {2.7559,2.4373},
        {2.6985,2.3946},
        {2.6425,2.3506},
        {2.5866,2.3067},
        {2.5302,2.263},
        {2.4753,2.2178},
        {2.4198,2.1733},
        {2.3649,2.1283},
        {2.3098,2.0833},
        {2.2555,2.0375},
        {2.2012,1.9918},
        {2.1468,1.9463},
        {2.0927,1.9002},
        {2.0391,1.8538},
        {1.9852,1.8079},
        {1.9318,1.7615},
        {1.878,1.7151},
        {1.8251,1.6679},
        {1.7714,1.6216},
        {1.7184,1.5743},
        {1.6655,1.5273},
        {1.6122,1.4805},
        {1.5596,1.433},
        {1.507,1.3858},
        {1.4538,1.339},
        {1.402,1.2908},
        {1.3488,1.2441},
        {1.2968,1.196},
        {1.2442,1.1487},
        {1.1918,1.101},
        {1.1394,1.0532},
        {1.0875,1.0052},
        {1.0348,0.9579},
        {0.9832,0.9096},
        {0.9306,0.8621},
        {0.879,0.8137},
        {0.8265,0.7662},
        {0.7743,0.7176},
        {0.7228,0.6695},
        {0.6706,0.6222},
        {0.6189,0.5738},
        {0.5671,0.5258},
        {0.5146,0.4775},
        {0.4632,0.4288},
        {0.411,0.3813},
        {0.3591,0.3326},
        {0.3074,0.2845},
        {0.2547,0.2359},
        {0.2036,0.1873},
        {0.1523,0.1405},
        {0.0962,0.0885},
        {0.0337,0.0296}
    };

Trajectory path1 = {
        {0,0},
        {0.041,0.0369},
        {0.0972,0.0856},
        {0.1615,0.1406},
        {0.2273,0.1953},
        {0.2918,0.2494},
        {0.3563,0.3039},
        {0.4221,0.3588},
        {0.4881,0.4133},
        {0.5532,0.4675},
        {0.6181,0.5227},
        {0.6847,0.5761},
        {0.7492,0.6313},
        {0.8158,0.6849},
        {0.8812,0.7393},
        {0.9472,0.7934},
        {1.0134,0.8474},
        {1.0798,0.9007},
        {1.1453,0.9549},
        {1.2122,1.0081},
        {1.2789,1.0614},
        {1.3454,1.1149},
        {1.4129,1.1676},
        {1.4801,1.2203},
        {1.5471,1.2732},
        {1.6148,1.3255},
        {1.6828,1.3777},
        {1.7513,1.4291},
        {1.8189,1.4813},
        {1.8881,1.5322},
        {1.9569,1.5835},
        {2.0267,1.6337},
        {2.0961,1.6843},
        {2.1666,1.7336},
        {2.2363,1.7837},
        {2.3075,1.8327},
        {2.3795,1.8808},
        {2.4515,1.9288},
        {2.5232,1.977},
        {2.5968,2.0235},
        {2.6705,2.0697},
        {2.7444,2.1156},
        {2.8192,2.161},
        {2.8959,2.2043},
        {2.9716,2.2485},
        {3.0487,2.2915},
        {3.128,2.3321},
        {3.2063,2.3737},
        {3.2867,2.4134},
        {3.3676,2.4524},
        {3.4502,2.4899},
        {3.5345,2.5256},
        {3.6179,2.5621},
        {3.7054,2.5947},
        {3.792,2.628},
        {3.8812,2.6588},
        {3.9714,2.6887},
        {4.0637,2.7164},
        {4.1565,2.7418},
        {4.1738,2.7042},
        {4.1378,2.6368},
        {4.0998,2.5761},
        {4.0639,2.5179},
        {4.0295,2.4629},
        {3.999,2.4084},
        {3.9679,2.3592},
        {3.9407,2.3105},
        {3.9142,2.2659},
        {3.8908,2.2224},
        {3.8672,2.1837},
        {3.8475,2.1456},
        {3.8288,2.1108},
        {3.8119,2.0788},
        {3.7959,2.0502},
        {3.7831,2.023},
        {3.7704,2},
        {3.7593,1.9798},
        {3.7512,1.961},
        {3.744,1.9457},
        {3.7383,1.9334},
        {3.7327,1.9254},
        {3.7308,1.9181},
        {3.7305,1.9137},
        {3.7294,1.9145},
        {3.7314,1.9167},
        {3.7349,1.922},
        {3.7399,1.9302},
        {3.7465,1.9414},
        {3.754,1.9564},
        {3.7645,1.9729},
        {3.7746,1.9946},
        {3.7885,2.0172},
        {3.8034,2.0436},
        {3.8194,2.0738},
        {3.8373,2.1069},
        {3.8591,2.1413},
        {3.8796,2.1819},
        {3.9054,2.2226},
        {3.9308,2.2689},
        {3.9602,2.3166},
        {3.9907,2.3686},
        {4.0237,2.424},
        {4.0603,2.4815},
        {4.0983,2.5435},
        {4.1392,2.609},
        {4.1835,2.6775},
        {4.2307,2.7487},
        {4.2764,2.823},
        {4.3227,2.8968},
        {4.3681,2.9714},
        {4.4123,3.0471},
        {4.4555,3.1239},
        {4.4994,3.2001},
        {4.5417,3.2778},
        {4.5843,3.3552},
        {4.6262,3.4332},
        {4.6676,3.5118},
        {4.7096,3.5899},
        {4.7513,3.6682},
        {4.7921,3.7474},
        {4.8341,3.8255},
        {4.8754,3.9041},
        {4.9165,3.9829},
        {4.958,4.0614},
        {4.9999,4.1396},
        {5.0413,4.2182},
        {5.0833,4.2962},
        {5.125,4.3745},
        {5.1664,4.4519},
        {5.1348,4.4603},
        {5.051,4.4242},
        {4.9673,4.3878},
        {4.8852,4.35},
        {4.8043,4.3108},
        {4.7247,4.2705},
        {4.6463,4.2289},
        {4.5688,4.1864},
        {4.4925,4.1426},
        {4.417,4.0982},
        {4.3424,4.0528},
        {4.2685,4.0067},
        {4.1955,3.9596},
        {4.1231,3.9121},
        {4.0514,3.8638},
        {3.9803,3.8149},
        {3.9097,3.7654},
        {3.8397,3.7155},
        {3.7702,3.6649},
        {3.7012,3.614},
        {3.6326,3.5625},
        {3.5645,3.5106},
        {3.4968,3.4584},
        {3.4295,3.4056},
        {3.3625,3.3526},
        {3.2959,3.2992},
        {3.2297,3.2454},
        {3.1638,3.1913},
        {3.0982,3.1369},
        {3.0329,3.0822},
        {2.968,3.0271},
        {2.9033,2.9718},
        {2.839,2.9162},
        {2.7749,2.8602},
        {2.711,2.8041},
        {2.6474,2.7477},
        {2.5842,2.6909},
        {2.521,2.6341},
        {2.4584,2.5767},
        {2.3957,2.5194},
        {2.3334,2.4617},
        {2.2715,2.4037},
        {2.2096,2.3456},
        {2.1479,2.2872},
        {2.0867,2.2285},
        {2.0254,2.1697},
        {1.9646,2.1106},
        {1.9038,2.0513},
        {1.8435,1.9917},
        {1.7831,1.9321},
        {1.7231,1.872},
        {1.6631,1.8118},
        {1.6034,1.7515},
        {1.5441,1.691},
        {1.485,1.6301},
        {1.4258,1.5692},
        {1.367,1.5081},
        {1.3083,1.4468},
        {1.25,1.3851},
        {1.1914,1.3234},
        {1.1332,1.2618},
        {1.0755,1.1995},
        {1.0175,1.1374},
        {0.9598,1.075},
        {0.9021,1.0127},
        {0.8451,0.9498},
        {0.7876,0.8874},
        {0.7308,0.8242},
        {0.6734,0.7615},
        {0.6168,0.6983},
        {0.5601,0.6352},
        {0.5033,0.5718},
        {0.4465,0.5082},
        {0.3898,0.4449},
        {0.3337,0.3814},
        {0.2773,0.3178},
        {0.2206,0.2537},
        {0.164,0.1902},
        {0.1083,0.1266},
        {0.0511,0.0617}
    };

void awp() {

  chassis.set_angle(45);

  actuateBoost();

  chassis.set_drive_pid(4, 20, true);
  cataRoller(170);
  chassis.set_drive_pid(-22, 50, true);
  chassis.wait_until(-1);
  cataIntake();//100
  chassis.wait_drive();

  chassis.set_turn_pid(165.5, 120);
  chassis.wait_drive();

  wait(100);

  cataShoot();

  wait(300);

  actuateBoost();

  chassis.set_turn_pid(47.2, 120);
  chassis.wait_drive();

  actuateIntake();

  cataIntake();
  
  chassis.set_drive_pid(-6.5, 80, true);
  chassis.wait_until(-6.25);
  actuateIntake();
  chassis.wait_drive();

  wait(400);

  chassis.set_drive_pid(6, 40);
  chassis.wait_drive();

  wait(200);

  chassis.set_drive_pid(-6, 40);
  chassis.wait_drive();

  chassis.set_turn_pid(161, 120);
  chassis.wait_drive();

  actuateBoost();

  wait(100);

  cataShoot();

  wait(300);

  actuateBoost();

  chassis.set_turn_pid(43, 120);
  chassis.wait_drive();

  cataIntake();//95

  chassis.set_drive_pid(-89, 75, true);
  chassis.wait_drive();

  chassis.set_turn_pid(110, 120);
  chassis.wait_drive();

  actuateBoost();

  wait(100);

  cataShoot();

  wait(300);

  releaseBoost();

  actuateBoost();

  chassis.set_turn_pid(43, 120);
  chassis.wait_drive();

  chassis.set_drive_pid(-18, 120);
  chassis.wait_until(-17);

  chassis.set_turn_pid(90, 120);
  chassis.wait_until(86);

  chassis.set_drive_pid(-10, 100);
  cataRoller(375);
  chassis.set_drive_pid(5, 70, true);




  //chassis.set_mode(ez::DISABLE);
  //followPath(path);
  //followPath(path1);
  //chassis.set_drive_pid(24, 80, true);
  //chassis.wait_drive();

  //chassis.set_swing_pid(ez::LEFT_SWING, 180, 90);
  //chassis.wait_drive();

  //chassis.set_turn_pid(90, 120);
  //chassis.wait_drive();

  //chassis.set_swing_pid(ez::LEFT_SWING, 0, 90);
  //chassis.wait_drive();

  //chassis.set_drive_pid(-24, 80, true);
  //chassis.wait_drive();

  //chassis.set_turn_pid(0, 120);
  //chassis.wait_drive();
}

void left_auton() {

  chassis.set_angle(-45);

  actuateBoost();

  chassis.set_drive_pid(4, 40, true);
  cataRoller(180);
  chassis.set_drive_pid(-6.5, 100, true);
  chassis.wait_until(-2);
  cataIntake();//110
  chassis.wait_drive();

  chassis.set_turn_pid(-124.5, 120);
  chassis.wait_drive();

  chassis.set_drive_pid(21, 100, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-198, 120);
  chassis.wait_drive();

  //chassis.set_drive_pid(13, 120, true);
  //chassis.wait_drive();

  wait(100);

  cataShoot();

  wait(300);

  actuateBoost();

  actuateIntake();

  wait(200);

  chassis.set_turn_pid(-52.5, 120);
  chassis.wait_drive();

  chassis.set_drive_pid(-5.50, 80, true);
  chassis.wait_drive();

  cataIntake();//115
  
  actuateIntake();

  wait(400);

  chassis.set_drive_pid(6.4, 50, true);
  chassis.wait_drive();

  wait(200);

  chassis.set_drive_pid(-6.1, 40, true);
  chassis.wait_drive();

  wait(200);

  chassis.set_turn_pid(-194, 120);
  chassis.wait_drive();

  chassis.set_drive_pid(-5, 80, true);
  chassis.wait_drive();

  actuateBoost();
  
  wait(150);

  cataShoot();

  wait(300);

  actuateBoost();

  chassis.set_turn_pid(-306, 120);
  chassis.wait_drive();

  actuateIntake();

  wait(100);

  chassis.set_drive_pid(-12, 35, true);
  chassis.wait_drive();

  actuateIntake();

  wait(400);

  chassis.set_drive_pid(6.2, 50);
  chassis.wait_drive();

  wait(200);

  chassis.set_drive_pid(-6, 40);
  chassis.wait_drive();

  wait(200);

  chassis.set_turn_pid(-200, 120);
  chassis.wait_drive();

  chassis.set_drive_pid(-4, 35, true);
  chassis.wait_drive();

  actuateBoost();
  
  wait(150);

  cataShoot();

  wait(300);

  //releaseBoost();

  actuateBoost();


}

void right_auton() {

  chassis.set_angle(-45);

  actuateBoost();

  cataIntake(30);

  chassis.set_drive_pid(-23.4, 100);
  chassis.wait_drive();

  cataIntake();

  chassis.set_drive_pid(-2, 100, true);
  chassis.wait_drive();

  wait(200);

  chassis.set_drive_pid(9.25, 35, true);
  chassis.wait_drive();

  chassis.set_turn_pid(105, 120);
  chassis.wait_drive();

  wait(100);

  cataShoot();

  wait(300);

  actuateBoost();

  chassis.set_turn_pid(225, 120);
  chassis.wait_drive();

  cataIntake(0);

  chassis.set_drive_pid(17, 90, true);
  chassis.wait_drive();

  chassis.set_drive_pid(5, 80, true);
  cataRoller(200);

  chassis.set_drive_pid(-61, 100, true);//100 speed
  chassis.wait_until(-10);
  cataIntake();//120
  chassis.wait_drive();

  wait(300);

  chassis.set_turn_pid(130, 120);
  chassis.wait_drive();

  //chassis.set_drive_pid(2, 60);
  //chassis.wait_drive();

  wait(100);

  cataShoot();

  wait(700);

  chassis.set_turn_pid(135, 120);
  chassis.wait_drive();

  chassis.set_drive_pid(-8, 60);
  chassis.wait_drive();

  cataIntake(110);//110

  chassis.set_turn_pid(104, 120);
  chassis.wait_drive();

  chassis.set_drive_pid(-21, 30);// 30 speed
  chassis.wait_drive();

  chassis.set_drive_pid(13.5, 50);
  chassis.wait_drive();

  chassis.set_turn_pid(131, 120);
  chassis.wait_drive();

  actuateBoost();

  wait(100);

  cataShoot();

  wait(300);

  actuateBoost();

  //releaseBoost();
  
  cataIntake(0);
}

void left_special() {

  actuateBoost();

  cataIntake(30);

  chassis.set_drive_pid(-10.5, 120);
  chassis.wait_until(-10);
  cataIntake();
  chassis.wait_drive();

  wait(100);

  chassis.set_drive_pid(16, 90, true);
  chassis.wait_until(15);
  cataIntake(0);
  chassis.wait_drive();

  chassis.set_drive_pid(4, 50);
  cataRoller(175);

  chassis.set_drive_pid(-6, 80, true);
  chassis.wait_drive();

  cataIntake();//110

  chassis.set_turn_pid(45, 120);
  chassis.wait_drive();

  chassis.set_drive_pid(-13, 80, true);
  chassis.wait_drive();
  
  chassis.set_turn_pid(166, 120);
  chassis.wait_drive();

  wait(100);

  cataShoot();

  wait(300);

  actuateBoost();

  chassis.set_turn_pid(45, 120);
  chassis.wait_drive();

  actuateIntake();

  chassis.set_drive_pid(-9, 80, true);
  chassis.wait_drive();

  actuateIntake();

  wait(400);

  chassis.set_drive_pid(6, 50);
  chassis.wait_drive();

  wait(200);

  chassis.set_drive_pid(-6, 40);
  chassis.wait_drive();

  //wait(200);

  chassis.set_drive_pid(-24, 90);
  chassis.wait_drive();

  chassis.set_turn_pid(146, 120);
  chassis.wait_drive();

  chassis.set_drive_pid(4, 90);
  chassis.wait_drive();

  //wait(100);

  cataShoot();

  wait(200);

  chassis.set_turn_pid(103, 120);
  chassis.wait_drive();

  chassis.set_drive_pid(-14.25, 80);
  chassis.wait_drive();

  chassis.set_turn_pid(165, 120);
  chassis.wait_drive();

  chassis.set_drive_pid(-20, 55);
  chassis.wait_drive();

  chassis.set_drive_pid(16, 90);
  chassis.wait_drive();

  chassis.set_turn_pid(140, 120);
  chassis.wait_drive();

  actuateBoost();

  wait(100);

  cataShoot();

  wait(300);

  actuateBoost();

  //releaseBoost();

  cataIntake(0);

}

void right_special() {

  chassis.set_angle(-45);

  //actuateBoost();

  chassis.set_turn_pid(-90, 120);
  chassis.wait_drive();

  cataIntake();//100

  chassis.set_drive_pid(-17, 90);
  chassis.wait_drive();

  chassis.set_turn_pid(-246, 120);
  chassis.wait_drive();

  actuateBoost();

  wait(100);

  cataShoot();

  wait(300);

  actuateBoost();

  chassis.set_turn_pid(-60, 120);
  chassis.wait_drive();

  wait(200);
  
  chassis.set_drive_pid(-12, 80);
  chassis.wait_drive();

  chassis.set_drive_pid(8, 90);
  chassis.wait_drive();

  chassis.set_turn_pid(-136.5, 120);
  chassis.wait_drive();

  cataIntake(0);

  chassis.set_drive_pid(33.5, 110);
  chassis.wait_drive();

  chassis.set_drive_pid(4, 70);
  cataRoller(350);

  chassis.set_drive_pid(-64.25, 110);
  chassis.wait_until(-10);
  cataIntake();//120
  chassis.wait_drive();

  wait(200);

  chassis.set_turn_pid(-227, 120);
  chassis.wait_drive();

  chassis.set_drive_pid(5, 100);
  chassis.wait_drive();

  wait(10);

  cataShoot();

  wait(200);

  chassis.set_turn_pid(-224, 120);
  chassis.wait_drive();

  cataIntake();

  wait(300);

  chassis.set_drive_pid(-10.25, 60);
  chassis.wait_drive();

  chassis.set_turn_pid(-256.25, 120);
  chassis.wait_drive();

  chassis.set_drive_pid(-21, 32);
  chassis.wait_until(-15);
  cataIntake();//90
  chassis.wait_drive();

  chassis.set_drive_pid(14.5, 80);
  chassis.wait_drive();

  cataIntake();

  chassis.set_turn_pid(-228, 120);
  chassis.wait_drive();

  actuateBoost();

  wait(100);

  cataShoot();

  wait(300);

  releaseBoost();

  actuateBoost();
  
  cataIntake(0);



}

