#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class DecisionTree {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        if (x[5] <= 29.5) {
                            if (x[7] <= 34.0) {
                                if (x[5] <= 18.0) {
                                    if (x[6] <= 3.5) {
                                        return 3;
                                    }

                                    else {
                                        if (x[7] <= 21.5) {
                                            return 2;
                                        }

                                        else {
                                            return 1;
                                        }
                                    }
                                }

                                else {
                                    return 4;
                                }
                            }

                            else {
                                return 5;
                            }
                        }

                        else {
                            return 6;
                        }
                    }

                protected:
                };
            }
        }
    }

    Eloquent::ML::Port::DecisionTree model;