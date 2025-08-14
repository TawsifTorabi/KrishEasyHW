#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class RandomForest {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        uint8_t votes[7] = { 0 };
                        // tree #1
                        if (x[5] <= 29.5) {
                            if (x[4] <= 3.5) {
                                if (x[1] <= 63.0) {
                                    if (x[7] <= 23.0) {
                                        if (x[6] <= 16.5) {
                                            votes[2] += 1;
                                        }

                                        else {
                                            votes[0] += 1;
                                        }
                                    }

                                    else {
                                        if (x[1] <= 59.0) {
                                            votes[5] += 1;
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }
                                }

                                else {
                                    if (x[6] <= 4.5) {
                                        votes[5] += 1;
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
                                }
                            }

                            else {
                                if (x[2] <= 56.5) {
                                    if (x[7] <= 15.5) {
                                        if (x[4] <= 6.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            votes[2] += 1;
                                        }
                                    }

                                    else {
                                        if (x[6] <= 13.0) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[0] += 1;
                                        }
                                    }
                                }

                                else {
                                    votes[3] += 1;
                                }
                            }
                        }

                        else {
                            votes[6] += 1;
                        }

                        // tree #2
                        if (x[7] <= 34.0) {
                            if (x[3] <= 2.5) {
                                if (x[0] <= 27.0) {
                                    if (x[7] <= 15.5) {
                                        if (x[2] <= 44.0) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            votes[2] += 1;
                                        }
                                    }

                                    else {
                                        if (x[6] <= 8.0) {
                                            votes[4] += 1;
                                        }

                                        else {
                                            votes[0] += 1;
                                        }
                                    }
                                }

                                else {
                                    if (x[5] <= 24.5) {
                                        if (x[6] <= 11.5) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[2] += 1;
                                        }
                                    }

                                    else {
                                        votes[6] += 1;
                                    }
                                }
                            }

                            else {
                                if (x[1] <= 61.0) {
                                    if (x[2] <= 43.0) {
                                        if (x[7] <= 17.0) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            votes[4] += 1;
                                        }
                                    }

                                    else {
                                        if (x[1] <= 57.0) {
                                            votes[0] += 1;
                                        }

                                        else {
                                            votes[3] += 1;
                                        }
                                    }
                                }

                                else {
                                    if (x[6] <= 10.5) {
                                        if (x[4] <= 6.0) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[4] += 1;
                                        }
                                    }

                                    else {
                                        votes[2] += 1;
                                    }
                                }
                            }
                        }

                        else {
                            votes[5] += 1;
                        }

                        // tree #3
                        if (x[6] <= 3.5) {
                            if (x[5] <= 29.5) {
                                if (x[2] <= 31.5) {
                                    votes[5] += 1;
                                }

                                else {
                                    if (x[7] <= 16.5) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[4] <= 1.5) {
                                            votes[5] += 1;
                                        }

                                        else {
                                            votes[4] += 1;
                                        }
                                    }
                                }
                            }

                            else {
                                votes[6] += 1;
                            }
                        }

                        else {
                            if (x[6] <= 15.5) {
                                if (x[7] <= 18.5) {
                                    votes[2] += 1;
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        // tree #4
                        if (x[5] <= 18.0) {
                            if (x[6] <= 3.5) {
                                if (x[7] <= 25.0) {
                                    votes[3] += 1;
                                }

                                else {
                                    votes[5] += 1;
                                }
                            }

                            else {
                                if (x[5] <= 9.5) {
                                    if (x[6] <= 13.0) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        votes[0] += 1;
                                    }
                                }

                                else {
                                    if (x[6] <= 9.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[7] <= 15.5) {
                                            votes[2] += 1;
                                        }

                                        else {
                                            votes[0] += 1;
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            if (x[7] <= 9.0) {
                                votes[6] += 1;
                            }

                            else {
                                votes[4] += 1;
                            }
                        }

                        // tree #5
                        if (x[7] <= 4.0) {
                            votes[6] += 1;
                        }

                        else {
                            if (x[1] <= 53.5) {
                                if (x[5] <= 8.0) {
                                    votes[0] += 1;
                                }

                                else {
                                    if (x[7] <= 14.0) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[4] <= 4.5) {
                                            votes[5] += 1;
                                        }

                                        else {
                                            votes[2] += 1;
                                        }
                                    }
                                }
                            }

                            else {
                                if (x[6] <= 3.5) {
                                    if (x[7] <= 28.5) {
                                        if (x[2] <= 32.0) {
                                            votes[4] += 1;
                                        }

                                        else {
                                            votes[3] += 1;
                                        }
                                    }

                                    else {
                                        votes[5] += 1;
                                    }
                                }

                                else {
                                    if (x[5] <= 11.0) {
                                        if (x[6] <= 11.5) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[2] += 1;
                                        }
                                    }

                                    else {
                                        if (x[1] <= 60.0) {
                                            votes[0] += 1;
                                        }

                                        else {
                                            votes[2] += 1;
                                        }
                                    }
                                }
                            }
                        }

                        // tree #6
                        if (x[7] <= 33.5) {
                            if (x[6] <= 3.5) {
                                if (x[5] <= 17.5) {
                                    votes[3] += 1;
                                }

                                else {
                                    if (x[2] <= 49.0) {
                                        if (x[5] <= 30.0) {
                                            votes[4] += 1;
                                        }

                                        else {
                                            votes[6] += 1;
                                        }
                                    }

                                    else {
                                        votes[6] += 1;
                                    }
                                }
                            }

                            else {
                                if (x[0] <= 27.0) {
                                    if (x[6] <= 16.5) {
                                        votes[2] += 1;
                                    }

                                    else {
                                        votes[0] += 1;
                                    }
                                }

                                else {
                                    if (x[7] <= 21.5) {
                                        if (x[2] <= 47.5) {
                                            votes[0] += 1;
                                        }

                                        else {
                                            votes[2] += 1;
                                        }
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
                                }
                            }
                        }

                        else {
                            votes[5] += 1;
                        }

                        // tree #7
                        if (x[0] <= 27.5) {
                            if (x[5] <= 18.0) {
                                if (x[7] <= 14.5) {
                                    if (x[2] <= 35.5) {
                                        votes[2] += 1;
                                    }

                                    else {
                                        votes[3] += 1;
                                    }
                                }

                                else {
                                    votes[0] += 1;
                                }
                            }

                            else {
                                votes[4] += 1;
                            }
                        }

                        else {
                            if (x[5] <= 29.5) {
                                if (x[0] <= 36.5) {
                                    if (x[5] <= 9.5) {
                                        if (x[1] <= 56.0) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }

                                    else {
                                        if (x[6] <= 4.0) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            votes[0] += 1;
                                        }
                                    }
                                }

                                else {
                                    if (x[5] <= 10.0) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        votes[5] += 1;
                                    }
                                }
                            }

                            else {
                                votes[6] += 1;
                            }
                        }

                        // tree #8
                        if (x[0] <= 26.5) {
                            if (x[3] <= 1.5) {
                                if (x[3] <= 0.5) {
                                    votes[3] += 1;
                                }

                                else {
                                    if (x[5] <= 10.5) {
                                        votes[0] += 1;
                                    }

                                    else {
                                        if (x[2] <= 37.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            votes[4] += 1;
                                        }
                                    }
                                }
                            }

                            else {
                                if (x[4] <= 2.5) {
                                    if (x[7] <= 16.0) {
                                        votes[2] += 1;
                                    }

                                    else {
                                        votes[4] += 1;
                                    }
                                }

                                else {
                                    votes[4] += 1;
                                }
                            }
                        }

                        else {
                            if (x[1] <= 56.0) {
                                if (x[7] <= 14.5) {
                                    votes[6] += 1;
                                }

                                else {
                                    if (x[4] <= 7.0) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        votes[5] += 1;
                                    }
                                }
                            }

                            else {
                                if (x[2] <= 32.5) {
                                    if (x[6] <= 4.5) {
                                        if (x[1] <= 66.0) {
                                            votes[6] += 1;
                                        }

                                        else {
                                            votes[5] += 1;
                                        }
                                    }

                                    else {
                                        if (x[6] <= 13.0) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[0] += 1;
                                        }
                                    }
                                }

                                else {
                                    if (x[7] <= 34.5) {
                                        if (x[7] <= 25.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }

                                    else {
                                        votes[5] += 1;
                                    }
                                }
                            }
                        }

                        // tree #9
                        if (x[6] <= 3.5) {
                            if (x[1] <= 53.5) {
                                if (x[5] <= 16.5) {
                                    if (x[5] <= 11.5) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[0] <= 27.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            votes[5] += 1;
                                        }
                                    }
                                }

                                else {
                                    votes[4] += 1;
                                }
                            }

                            else {
                                if (x[7] <= 4.5) {
                                    votes[6] += 1;
                                }

                                else {
                                    if (x[4] <= 3.0) {
                                        if (x[5] <= 19.5) {
                                            votes[5] += 1;
                                        }

                                        else {
                                            votes[4] += 1;
                                        }
                                    }

                                    else {
                                        if (x[5] <= 18.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            votes[4] += 1;
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            if (x[7] <= 21.5) {
                                if (x[7] <= 15.5) {
                                    if (x[4] <= 0.5) {
                                        votes[0] += 1;
                                    }

                                    else {
                                        votes[2] += 1;
                                    }
                                }

                                else {
                                    votes[0] += 1;
                                }
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #10
                        if (x[5] <= 29.5) {
                            if (x[4] <= 2.5) {
                                if (x[7] <= 34.0) {
                                    if (x[3] <= 2.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[5] <= 18.0) {
                                            votes[2] += 1;
                                        }

                                        else {
                                            votes[4] += 1;
                                        }
                                    }
                                }

                                else {
                                    votes[5] += 1;
                                }
                            }

                            else {
                                if (x[7] <= 15.5) {
                                    if (x[1] <= 61.0) {
                                        if (x[6] <= 6.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            votes[2] += 1;
                                        }
                                    }

                                    else {
                                        if (x[3] <= 1.0) {
                                            votes[2] += 1;
                                        }

                                        else {
                                            votes[2] += 1;
                                        }
                                    }
                                }

                                else {
                                    if (x[6] <= 3.5) {
                                        if (x[0] <= 27.5) {
                                            votes[4] += 1;
                                        }

                                        else {
                                            votes[5] += 1;
                                        }
                                    }

                                    else {
                                        if (x[7] <= 24.5) {
                                            votes[0] += 1;
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            votes[6] += 1;
                        }

                        // return argmax of votes
                        uint8_t classIdx = 0;
                        float maxVotes = votes[0];

                        for (uint8_t i = 1; i < 7; i++) {
                            if (votes[i] > maxVotes) {
                                classIdx = i;
                                maxVotes = votes[i];
                            }
                        }

                        return classIdx;
                    }

                protected:
                };
            }
        }
    }

    Eloquent::ML::Port::RandomForest model;