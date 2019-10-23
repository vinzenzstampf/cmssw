int DoubleHTagProducer::chooseCategory( float mvavalue, float mxvalue)
    {
        //// should return 0 if mva above all the numbers, 1 if below the first, ..., boundaries.size()-N if below the Nth, ...
        //this is for mva, then you have mx
        if (!doCategorization_) {
            return 0;
        }
        int mvaCat=-1;
        for( int n = 0 ; n < ( int )mvaBoundaries_.size() ; n++ ) {
            if( ( double )mvavalue > mvaBoundaries_[mvaBoundaries_.size() - n - 1] ) {
                mvaCat = n;
                break;
            }
        }

        if (mvaCat==-1) return -1;// Does not pass, object will not be produced

        int mxCat=-1;
        for( int n = 0 ; n < ( int )mxBoundaries_.size() ; n++ ) {
            if( ( double )mxvalue > mxBoundaries_[mxBoundaries_.size() - n - 1] ) {
                mxCat = n;
                break;
            }
        }


        if (mxCat==-1) return -1;// Does not pass, object will not be produced

        int cat=-1;
        cat = mvaCat*mxBoundaries_.size()+mxCat;

        //the schema is like this: (different from HHbbgg_ETH)
        //            "cat0 := MXbin0 * MVAcat0",   #High MX, High MVA
        //            "cat1 := MXbin1 * MVAcat0",   #High but lower MX , High MVA
        //            "cat2 := MXbin2 * MVAcat0",
        //            "cat3 := MXbin0 * MVAcat1",
        //            "cat4 := MXbin1 * MVAcat1",
        // [.................................]

        return cat;

    }
