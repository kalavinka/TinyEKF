#include "tinyekf.h"

class Fuser : public TinyEKF {

    public:

        // Eight state values, four measurement values
        Fuser() : TinyEKF(1, 1)
        {            
            this->setP(0, 0, .01);
            this->setQ(0, 0, .01);
            this->setR(0, 0, .01);

        }

    protected:

        void model(float * fx, float * F, float * hx, float * H)
        {
            fx[0] = this->x[0];
            hx[0] = fx[0];

            set(F, 0, 0, 1);
            set(H, 0, 0, 1);
        }
};

int main(int argc, char ** argv)
{    
    // Create the EKF
    Fuser ekf;

    static const int STEPS = 1000;

    // Loop till no more data
    for (int i=0; i<STEPS; ++i) {

        float z[1];

        z[0] = sin(2*M_PI*i/STEPS);

        ekf.step(z);

        printf("%f\n", ekf.getX(0));
    }
}