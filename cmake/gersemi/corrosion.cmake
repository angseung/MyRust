# Signature stubs of Corrosion v0.5.1 public commands, used only by gersemi
# (see `definitions` in .gersemirc) so it knows their keywords and formats them
# correctly. This file is NOT included by the build.
# Keywords copied from _deps/corrosion-src/cmake/Corrosion.cmake (v0.5.1).

function(corrosion_import_crate)
  cmake_parse_arguments(
    COR
    "ALL_FEATURES;NO_DEFAULT_FEATURES;NO_STD;NO_LINKER_OVERRIDE;LOCKED;FROZEN"
    "MANIFEST_PATH;PROFILE;IMPORTED_CRATES"
    "CRATE_TYPES;CRATES;FEATURES;FLAGS"
    ${ARGN}
  )
endfunction()

function(corrosion_set_linker_language target_name language)
endfunction()

function(corrosion_set_linker target_name linker)
endfunction()

function(corrosion_set_hostbuild target_name)
endfunction()

function(corrosion_add_target_rustflags target_name rustflag)
endfunction()

function(corrosion_add_target_local_rustflags target_name rustc_flag)
endfunction()

function(corrosion_set_env_vars target_name env_var)
endfunction()

function(corrosion_set_cargo_flags target_name)
endfunction()

function(corrosion_set_features target_name)
  cmake_parse_arguments(
    SET_FEATURES
    "NO_DEFAULT_FEATURES"
    "ALL_FEATURES"
    "FEATURES"
    ${ARGN}
  )
endfunction()

function(corrosion_link_libraries target_name)
endfunction()

function(corrosion_install)
  cmake_parse_arguments(
    COR_INSTALL
    ""
    "EXPORT;DESTINATION"
    "TARGETS;ARCHIVE;LIBRARY;RUNTIME;PRIVATE_HEADER;PUBLIC_HEADER;PERMISSIONS;CONFIGURATIONS"
    ${ARGN}
  )
endfunction()

function(corrosion_add_cxxbridge cxx_target)
  cmake_parse_arguments(_arg "" "CRATE" "FILES" ${ARGN})
endfunction()

function(corrosion_experimental_cbindgen)
  cmake_parse_arguments(
    CCN
    ""
    "TARGET;MANIFEST_DIRECTORY;HEADER_NAME;CBINDGEN_VERSION"
    "FLAGS"
    ${ARGN}
  )
endfunction()
