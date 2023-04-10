# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
from collections import defaultdict
from pathlib import Path
import logging
import json
import matplotlib.pyplot as plt
import pandas as pd
import re

LOG = logging.getLogger(__name__)

def make_plot(report_path: Path, output: Path):
    LOG.info(f"Making plot for {report_path}...")
    with open(report_path) as f:
        benchmarks = json.load(f)["benchmarks"]


    casts = defaultdict(dict)
    index = set()

    for bench in benchmarks:
        # We expect following format:
        #    InheritanceFixture/deep_fromBase_dynamic_cast
        parts = re.split("/|_", bench["run_name"])
        direction = f"{parts[1]}, {parts[2]}"
        kind = "_".join(parts[3:])
        casts[kind][direction] = bench["cpu_time"]
        index.add(direction)

    index = sorted(index)
    data = {
        kind: [casts[kind].get(direction, None) for direction in index]
        for kind in casts
    }

    data = pd.DataFrame(data, index=index)
    time_unit = benchmarks[0]["time_unit"]

    ax = data.plot(kind="barh", xlabel=time_unit)
    plt.tight_layout()
    plt.savefig(output)
    plt.clf()

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--benchmark", type=Path,
        help="Path to benchmark JSON file.",
        required=True,
    )
    parser.add_argument(
        "--output", type=Path,
        help="Path to output PNG file.",
        required=True,
    )
    args = parser.parse_args()

    make_plot(args.benchmark, args.output)