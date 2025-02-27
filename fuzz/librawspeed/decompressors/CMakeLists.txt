macro(add_simple_fuzzer name)
  set(TheFuzzer "${name}Fuzzer")
  rawspeed_add_executable(${TheFuzzer} "${name}.cpp")

  add_fuzz_target(${TheFuzzer})

  add_dependencies(fuzzers ${TheFuzzer})
endmacro()

add_subdirectory(HuffmanTable)

set(DECOMPRESSORS
  "Cr2LJpegDecoder"
  "CrwDecompressor"
  "DummyLJpegDecompressor"
  "FujiDecompressor"
  "HasselbladDecompressor"
  "KodakDecompressor"
  "LJpegDecompressor"
  "NikonDecompressor"
  "OlympusDecompressor"
  "PanasonicV4Decompressor"
  "PanasonicV5Decompressor"
  "PanasonicV6Decompressor"
  "PentaxDecompressor"
  "PhaseOneDecompressor"
  "SamsungV0Decompressor"
  "SamsungV1Decompressor"
  "SamsungV2Decompressor"
  "SonyArw1Decompressor"
  "SonyArw2Decompressor"
  "VC5Decompressor"
)

foreach(decompressor ${DECOMPRESSORS})
  add_simple_fuzzer(${decompressor})
endforeach()


function(add_specialized_fuzzer Name HuffmanTableImpl)
  set(fuzzer "${Name}Fuzzer-${HuffmanTableImpl}")

  rawspeed_add_executable(${fuzzer} ${Name}.cpp)
  target_compile_definitions(${fuzzer}
    PRIVATE
    -DHuffmanTableImpl=${HuffmanTableImpl}
    -DWITH_${HuffmanTableImpl}
  )

  add_fuzz_target(${fuzzer})

  add_dependencies(HuffmanTableFuzzers ${fuzzer})
endfunction()

add_specialized_fuzzer("Cr2Decompressor" HuffmanTable)
add_specialized_fuzzer("Cr2Decompressor" DummyHuffmanTable)
