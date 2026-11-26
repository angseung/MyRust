/// Returns the sum of two integers. Exposed with the C ABI so it can be
/// called from C/C++.
/// Uses wrapping_add so overflow wraps around instead of panicking
/// (a panic propagating across the FFI boundary aborts the process).
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
