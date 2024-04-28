#include <eml_trees.h>
    

static const EmlTreesNode xor_model_nodes[14] = {
  { 1, 0.197349f, 1, 2 },
  { 0, 0.466316f, -1, -2 },
  { 1, 0.256702f, 1, 2 },
  { 0, 0.464752f, -1, -2 },
  { 0, 0.476659f, -2, -1 },
  { 1, 0.897163f, 1, -2 },
  { 0, 0.504671f, 1, 2 },
  { 1, 0.501874f, -1, -2 },
  { 1, 0.498237f, -2, -1 },
  { 0, 0.119730f, 1, 2 },
  { 1, 0.394697f, -1, -2 },
  { 1, 0.261566f, 1, 2 },
  { 0, 0.473531f, -1, -2 },
  { 0, 0.421164f, -2, -1 } 
};

static const int32_t xor_model_tree_roots[3] = { 0, 5, 9 };

static const uint8_t xor_model_leaves[2] = { 0, 1 };

EmlTrees xor_model = {
        14,
        (EmlTreesNode *)(xor_model_nodes),	  
        3,
        (int32_t *)(xor_model_tree_roots),
        2,
        (uint8_t *)(xor_model_leaves),
        0,
        2,
        2,
    };

static inline int32_t xor_model_tree_0(const float *features, int32_t features_length) {
          if (features[1] < 0.197349f) {
              if (features[0] < 0.466316f) {
                  return 0;
              } else {
                  return 1;
              }
          } else {
              if (features[1] < 0.256702f) {
                  if (features[0] < 0.464752f) {
                      return 0;
                  } else {
                      return 1;
                  }
              } else {
                  if (features[0] < 0.476659f) {
                      return 1;
                  } else {
                      return 0;
                  }
              }
          }
        }
        

static inline int32_t xor_model_tree_1(const float *features, int32_t features_length) {
          if (features[1] < 0.897163f) {
              if (features[0] < 0.504671f) {
                  if (features[1] < 0.501874f) {
                      return 0;
                  } else {
                      return 1;
                  }
              } else {
                  if (features[1] < 0.498237f) {
                      return 1;
                  } else {
                      return 0;
                  }
              }
          } else {
              return 1;
          }
        }
        

static inline int32_t xor_model_tree_2(const float *features, int32_t features_length) {
          if (features[0] < 0.119730f) {
              if (features[1] < 0.394697f) {
                  return 0;
              } else {
                  return 1;
              }
          } else {
              if (features[1] < 0.261566f) {
                  if (features[0] < 0.473531f) {
                      return 0;
                  } else {
                      return 1;
                  }
              } else {
                  if (features[0] < 0.421164f) {
                      return 1;
                  } else {
                      return 0;
                  }
              }
          }
        }
        

int32_t xor_model_predict(const float *features, int32_t features_length) {

        int32_t votes[2] = {0,};
        int32_t _class = -1;

        _class = xor_model_tree_0(features, features_length); votes[_class] += 1;
    _class = xor_model_tree_1(features, features_length); votes[_class] += 1;
    _class = xor_model_tree_2(features, features_length); votes[_class] += 1;
    
        int32_t most_voted_class = -1;
        int32_t most_voted_votes = 0;
        for (int32_t i=0; i<2; i++) {

            if (votes[i] > most_voted_votes) {
                most_voted_class = i;
                most_voted_votes = votes[i];
            }
        }
        return most_voted_class;
    }
    