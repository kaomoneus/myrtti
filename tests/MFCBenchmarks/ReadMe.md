Prereq: You need *Windows SDK 10* to be installed.

Assuming myrtti is located at `$MYRTTI_ROOT`

0. `cd $MYRTTI_ROOT`
1. `mkdir buildvs`
2. `cd buildvs`
3. `cmake .. -G  "Visual Studio 17 2022"`
4. `cmake --build . --config Release`
5. Open `$MYRTTI_ROOT/tests/MFCBenchmarks/MFCBenchmarks.sln`
6. Select "*Release*" configuration.
7. Build and run. Perhaps you have to run nuget
   manually (it will download `gbenchmark`).
