struct Xor_Basis {
    ull base[64];
    
    Xor_Basis () {
        mst(base, 0);
    }
    
    bool add (ull element) {
        RREP(i, 63, 0) {
            if (element & twop (i)) {
                if (base[i]) element ^= base[i];
                else {
                    base[i] = element;
                    return true;
                }
            }
        }
        return false;
    }
    
    ull find_max (ull element) const {
        RREP(i, 63, 0) {
            if (!(element & twop (i))) {
                element ^= base[i];
            }
        }
        return element;
    }
    
    ull find_min (ull element) const {
        RREP(i, 63, 0) {
            if ((element & twop (i))) {
                element ^= base[i];
            }
        }
        return element;
    }
};
