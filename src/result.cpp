#include <optional>

namespace std_gearlang {
    template <class T, class E>
    class Result {
    private:
        std::optional<T> ok_val;
        std::optional<E> err_val;
    
        Result(std::optional<T> val, std::optional<E> err) {
            ok_val = val;
            err_val = err;
        }
    public:
        static inline Result<T, E> ok(T val) {
            return Result(val, std::nullopt);
        }

        static inline Result<T, E> err(E val) {
            return Result(std::nullopt, val);
        }

        inline constexpr bool is_ok() {
            return !is_err();
        }

        inline constexpr bool is_err() {
            return err_val.value();
        }

        inline constexpr T unwrap() {
            if(is_err()) {
                throw 
            }
        }
    }
}