#include <vector>
using namespace std;

const int tag = 0;
const int coordinator_slave_id = 0; // l'id du coordinateur
const int calculator_slave_id = 1; // les id esclaves demarrent a 1

vector<vector<float> > temperature_matrix;
vector<vector<int> > processes_matrix;


float get_initial_temperature(int process);

/**
 * returns the temperature of a given process
 */
float get_temperature(int process);
