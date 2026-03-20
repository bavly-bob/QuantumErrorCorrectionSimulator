class LogicalQubit {
private:
    QuantumState& state;
    int base;
    int repetition;

public:
    LogicalQubit(QuantumState& s, int base, int rep);

    void encode();
    void applyHadamard();
    void applyX();
    void applyY();
    void applyZ();
};