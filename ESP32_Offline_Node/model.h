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
                        uint8_t votes[2] = { 0 };
                        // tree #1
                        if (x[1] <= 21.285520553588867) {
                            if (x[0] <= 2.772122383117676) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #2
                        if (x[0] <= 2.6644222736358643) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #3
                        if (x[0] <= 2.879762291908264) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #4
                        if (x[0] <= 2.6644222736358643) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #5
                        if (x[1] <= 21.304993629455566) {
                            if (x[1] <= 20.348621368408203) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #6
                        if (x[1] <= 21.292881965637207) {
                            if (x[0] <= 2.772122383117676) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #7
                        if (x[0] <= 2.9874624013900757) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #8
                        if (x[0] <= 2.772122383117676) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #9
                        if (x[0] <= 2.647400975227356) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #10
                        if (x[1] <= 21.29090404510498) {
                            if (x[0] <= 2.772122383117676) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #11
                        if (x[0] <= 2.6644222736358643) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #12
                        if (x[1] <= 21.285520553588867) {
                            if (x[0] <= 2.772122383117676) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #13
                        if (x[0] <= 2.772122383117676) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #14
                        if (x[0] <= 2.6644222736358643) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #15
                        if (x[1] <= 21.304993629455566) {
                            if (x[1] <= 20.536667823791504) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #16
                        if (x[0] <= 2.9874624013900757) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #17
                        if (x[1] <= 21.29090404510498) {
                            if (x[1] <= 20.58788776397705) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #18
                        if (x[0] <= 2.772122383117676) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #19
                        if (x[0] <= 2.772122383117676) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #20
                        if (x[0] <= 2.772122383117676) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #21
                        if (x[1] <= 21.285520553588867) {
                            if (x[0] <= 2.772122383117676) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #22
                        if (x[1] <= 21.285520553588867) {
                            if (x[0] <= 3.700376510620117) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #23
                        if (x[0] <= 2.6644222736358643) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #24
                        if (x[1] <= 21.29090404510498) {
                            if (x[1] <= 20.541698455810547) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #25
                        if (x[1] <= 21.29090404510498) {
                            if (x[0] <= 2.6644222736358643) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #26
                        if (x[0] <= 2.772122383117676) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #27
                        if (x[1] <= 21.304993629455566) {
                            if (x[1] <= 20.541698455810547) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #28
                        if (x[0] <= 2.647400975227356) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #29
                        if (x[1] <= 21.29090404510498) {
                            if (x[1] <= 20.536667823791504) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #30
                        if (x[0] <= 2.772122383117676) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #31
                        if (x[0] <= 2.6644222736358643) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #32
                        if (x[1] <= 21.29090404510498) {
                            if (x[0] <= 2.772122383117676) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #33
                        if (x[1] <= 21.29090404510498) {
                            if (x[0] <= 2.993492603302002) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #34
                        if (x[0] <= 2.9874624013900757) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #35
                        if (x[0] <= 2.6644222736358643) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #36
                        if (x[1] <= 21.285520553588867) {
                            if (x[1] <= 20.541698455810547) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #37
                        if (x[0] <= 2.772122383117676) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #38
                        if (x[1] <= 21.28488063812256) {
                            if (x[1] <= 19.809450149536133) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #39
                        if (x[0] <= 2.772122383117676) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #40
                        if (x[0] <= 3.1506946086883545) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #41
                        if (x[1] <= 21.34118366241455) {
                            if (x[0] <= 2.6528486013412476) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #42
                        if (x[0] <= 3.0314208269119263) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #43
                        if (x[1] <= 21.29090404510498) {
                            if (x[0] <= 2.993492603302002) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #44
                        if (x[0] <= 2.9874624013900757) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #45
                        if (x[0] <= 2.772122383117676) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #46
                        if (x[1] <= 21.27879238128662) {
                            if (x[1] <= 20.536667823791504) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #47
                        if (x[1] <= 21.285520553588867) {
                            if (x[0] <= 2.772122383117676) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #48
                        if (x[0] <= 2.6524658203125) {
                            votes[0] += 1;
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #49
                        if (x[1] <= 21.29090404510498) {
                            if (x[0] <= 2.6644222736358643) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #50
                        if (x[1] <= 21.299610137939453) {
                            if (x[0] <= 2.772122383117676) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // return argmax of votes
                        uint8_t classIdx = 0;
                        float maxVotes = votes[0];

                        for (uint8_t i = 1; i < 2; i++) {
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