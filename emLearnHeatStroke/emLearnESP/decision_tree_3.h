#include <eml_trees.h>

static const EmlTreesNode tree_3_nodes[4] = {
  { 4, 38.640575f, 1, 3 },
  { 5, 0.394070f, 1, -1 },
  { 1, 100.617798f, -2, -2 },
  { 5, 0.099744f, -2, -1 } 
};

static const int32_t tree_3_tree_roots[1] = { 0 };

static const uint8_t tree_3_leaves[2] = { 1, 0 };

EmlTrees tree_3 = {
        4,
        (EmlTreesNode *)(tree_3_nodes),	  
        1,
        (int32_t *)(tree_3_tree_roots),
        2,
        (uint8_t *)(tree_3_leaves),
        0,
        7,
        2,
    };

static inline int32_t tree_3_tree_0(const float *features, int32_t features_length) {
          if (features[4] < 38.640575f) {
              if (features[5] < 0.394070f) {
                  if (features[1] < 100.617798f) {
                      return 0;
                  } else {
                      return 0;
                  }
              } else {
                  return 1;
              }
          } else {
              if (features[5] < 0.099744f) {
                  return 0;
              } else {
                  return 1;
              }
          }
        }
        

int32_t tree_3_predict(const float *features, int32_t features_length) {

        int32_t votes[2] = {0,};
        int32_t _class = -1;

        _class = tree_3_tree_0(features, features_length); votes[_class] += 1;
    
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
    
