#ifndef GLOBALS_H
#define GLOBALS_H
class globals {
public:
    static globals& instance() {
        static globals instance;
        return instance;
    }

    int getUserId() const {
        return userId;
    }

    void setUserId(int id) {
        userId = id;
    }

private:
    int userId;

    // Private constructor to enforce singleton pattern
    globals() : userId(-1) {}
};
#endif // GLOBALS_H
