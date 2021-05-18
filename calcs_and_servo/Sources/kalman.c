#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

float K_k, E_est, E_mea, x_hat;
 
float kalman_filter(float x){
    
    //obtaining z_k: my tank height = 25.4, calculates %
    //x = data input
    
    //innovation 
    K_k = E_est / (E_est + E_mea);
    x_hat = x_hat + K_k * (x - x_hat);
    E_est = (1 - K_k) * E_est;
    
    return x_hat;
}