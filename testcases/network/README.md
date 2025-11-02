# Network Protocol Test Cases for AFLNet

This directory contains network protocol test cases specifically designed for use with AFLNet, a greybox fuzzer for network protocols.

## RTSP Test Cases

The RTSP (Real Time Streaming Protocol) test cases in the `rtsp/` subdirectory are designed to test RTSP server implementations. These test cases represent valid RTSP message sequences that can be used as seed inputs for AFLNet fuzzing campaigns.

### Files:

- `basic_rtsp_request.raw`: Contains a basic RTSP request sequence including DESCRIBE, OPTIONS, SETUP, and PLAY commands. This represents a typical RTSP session flow.
- `edge_case_rtsp_request.raw`: Contains RTSP requests with edge cases and potentially problematic inputs, including malformed URLs and special characters.

## Usage with AFLNet

These test cases can be used as input seeds for AFLNet when fuzzing RTSP server implementations:

```bash
afl-fuzz -d -i /workspace/testcases/network/rtsp -o out-rtsp -N tcp://127.0.0.1/8554 -x /workspace/dictionaries/rtsp.dict -P RTSP -D 10000 ./rtsp_server
```

## Adding New Test Cases

When adding new test cases:
1. Follow the RTSP protocol specification
2. Ensure request sequences are logically ordered (e.g., SETUP after DESCRIBE)
3. Include proper RTSP headers like CSeq for ordering
4. Consider different protocol flows and edge cases