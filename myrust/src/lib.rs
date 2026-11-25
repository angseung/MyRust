/// 두 정수의 합을 반환한다. C/C++에서 호출할 수 있도록 C ABI로 노출.
/// 오버플로 시 panic 대신 wrap-around 되도록 wrapping_add 사용
/// (FFI 경계를 넘어 panic이 전파되면 프로세스가 abort 되므로).
#[no_mangle]
pub extern "C" fn add(a: i32, b: i32) -> i32 {
    a.wrapping_add(b)
}

#[no_mangle]
pub extern "C" fn mul(a: i32, b: i32) -> i32 {
    a.wrapping_mul(b)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_adds() {
        assert_eq!(add(2, 3), 5);
        assert_eq!(add(-4, 1), -3);
    }
}
