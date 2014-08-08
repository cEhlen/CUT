//
//  main.cpp
//  CUT
//
//  Created by Christoph Ehlen on 08/08/14.
//  Copyright (c) 2014 ColorFit. All rights reserved.
//

#include "CUT.h"

TEST({
    DESCRIBE(SUM, {
        IT(should return 2 for 1+1, {
            assert.equals(1+1, 2);
        });
        IT(should fail for 1.003 == 1.0, {
            assert.almost_equals(1.003, 1.0, 3);
        });
    });
});


