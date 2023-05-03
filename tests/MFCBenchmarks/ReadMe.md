Prereq: You need Windows SDK 10 to be installed.

1. In root of "myrtti" project create "build"
2. cd "build
3. cmake .. -G  "Visual Studio 17 2022"
4. cmake --build . --config Release
5. Open <myrtti-root>/tests/MFCBenchmarks/MFCBenchmarks.sln
6. Select "Release"
7. Build and run. Perhaps you have to run nuget
   manually (it will download gbenchmark).
