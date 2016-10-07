#ifndef LINEAR_SARSA_AGENT
#define LINEAR_SARSA_AGENT

#include <iostream>
#include <sstream>
#include "SMDPAgent.h"
#include "tiles2.h"

class WorldModel;

/**
 * Designed specifically to match the serialization format for collision_table.
 * See collision_table::save and collision_table::restore.
 */
#pragma pack(push, 1)
struct SharedData {
  int lastAction;
  int lastActionTime;
};
#pragma pack(pop)

namespace jol {

class LinearSarsaAgent : public SMDPAgent {
protected:
  string saveWeightsFile;
  bool bLearning;
  bool bSaveWeights;

  std::unordered_map<std::string, sem_t*> sems;
  string sharedMemoryName;
  SharedData *sharedData;

  double alpha;
  double gamma;
  double lambda;
  double epsilon;
  double initialWeight;

  double tileWidths[MAX_RL_STATE_VARS];
  double Q[MAX_RL_ACTIONS];

  double weights[RL_MEMORY_SIZE];

  int tiles[MAX_RL_ACTIONS][RL_MAX_NUM_TILINGS];
  int numTilings;

  double minimumTrace;
  int numNonzeroTraces;

  double traces[RL_MEMORY_SIZE];
  int nonzeroTraces[RL_MAX_NONZERO_TRACES];
  int nonzeroTracesInverse[RL_MEMORY_SIZE];

  collision_table *colTab;

  // Load / Save weights from/to disk
  bool loadWeights(const char *filename);

  bool saveWeights(const char *filename);

  // Value function methods for CMACs
  int selectAction();

  double computeQ(int a);

  int argmaxQ() const;

  void updateWeights(double delta);

  virtual void loadTiles(double state[]);

  // Eligibility trace methods
  void clearTrace(int f);

  void clearExistentTrace(int f, int loc);

  void decayTraces(double decayRate);

  void setTrace(int f, float newTraceValue);

  void increaseMinTrace();

  void loadSharedData(SharedData *address);

  void saveSharedData(SharedData *address);

  virtual void sync(bool load);

  double reward(double tau, double gamma);

  const std::vector<int> &validActions() const;

public:
  LinearSarsaAgent(WorldModel *wm,
                   int numFeatures,
                   bool bLearn,
                   double widths[],
                   std::string loadWeightsFile,
                   std::string saveWeightsFile,
                   double gamma,
                   double initialWeight);

  virtual ~LinearSarsaAgent();

  void setEpsilon(double epsilon);

  // SMDP Sarsa implementation
  int startEpisode(double state[]);

  int step(double reward_, double state[]);

  void endEpisode(double reward_);

  void shutDown();
};

}
#endif
