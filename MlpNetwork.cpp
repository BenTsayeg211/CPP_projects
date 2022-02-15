#include "MlpNetwork.h"
#define LAST_VECTOR_SIZE 10
/**
 * constructor
 * @param weights
 * @param biases
 */
MlpNetwork::MlpNetwork (const Matrix weights[],
                        const Matrix biases[])
{
  levels[0] = Dense (weights[0], biases[0], RELU);
  levels[1] = Dense (weights[1], biases[1], RELU);
  levels[2] = Dense (weights[2], biases[2], RELU);
  levels[3] = Dense (weights[3], biases[3], SOFTMAX);
}
/**
 * operate the process
 * @param numberPic
 * @return the digit in the image
 */

digit MlpNetwork::operator() (const Matrix &numberPic)
{
  Matrix helper = numberPic;
  for (int i = 0; i < MLP_SIZE; i++)
    {
      helper = levels[i] (helper);
    }
  unsigned int max_dig = 0;
  float max_prob = 0;
  for (int i = 0; i < LAST_VECTOR_SIZE; i++)
    {
      if (helper[i] > max_prob)
        {
          max_prob = helper[i];
          max_dig = i;
        }
    }
  digit ret_digit = {max_dig, max_prob};
  return ret_digit;
}