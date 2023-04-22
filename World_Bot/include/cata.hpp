enum cata_states { PRIME = 0, HOLD = 1, SHOOT = 2, INTAKE = 3};

void cataPrime();

void cataHold();

void cataShoot();

void cataIntake(int speed = 127);

void cataRoller(int time);

void cataWait();

void cataInitialize();

void wait(int msec);

extern bool bandCata;
