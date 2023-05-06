import argparse
import logging
import pathlib
from typing import List, TextIO

LOG = logging.getLogger("main")

MYRTTI_FILE_PREFIX = "myrtti"


def _lines(f: TextIO, lines: List[str]):
    for ln in lines:
        f.write(ln + "\n")


def emit_myrtti(name_base: str, depth: int, output: pathlib.Path):

    filename = output / f"{MYRTTI_FILE_PREFIX}_{name_base}.h"

    def cls_name(d: int):
        return f"MyRTTI_{name_base}_{d}"

    with open(filename, "w") as f:
        LOG.info(f"    myrtti: writing to {filename}")
        LOG.info(f"    myrtti:    writing {cls_name(0)}")
        _lines(f, [
            "#pragma once",
            "#include <myrtti.h>",
            "",
            f"RTTI_STRUCT_ROOT_BEGIN({cls_name(0)})",
            "RTTI_STRUCT_END();",
            "",
        ])

        for i in range(1, depth):
            LOG.info(f"    myrtti:    writing {cls_name(i)}")
            _lines(f, [
                f"RTTI_STRUCT_BEGIN({cls_name(i)}, ({cls_name(i-1)}))",
                "RTTI_STRUCT_END();",
                "",
            ])


def emit_ue(name_base: str, depth: int, output: pathlib.Path):

    def cls_name(d: int):
        return f"AUnreal_{name_base}_{d}"

    def emit_ue_class(name: str, parent: str, parent_header: str):
        header = output / f"{name}.h"
        cpp = output / f"{name}.cpp"
        with open(header, "w") as f:
            LOG.info(f"    ue:    writing {header}")
            _lines(f, [
                    "#pragma once",
                    "",
                    "#include \"CoreMinimal.h\"",
                    f"#include \"{parent_header}\"",
                    f"#include \"{name}.generated.h\"",
                    "",
                    "UCLASS()",
                    f"class {name} : public {parent}",
                    "{",
                    "	GENERATED_BODY()",
                    "	",
                    "public:	",
                    f"	{name}();",
                    "",
                    "};",
                ])

        with open(cpp, "w") as f:
            LOG.info(f"    ue:    writing {cpp}")
            _lines(f, [
                f"#include \"{name}.h\"",
                "",
                f"{name}::{name}()",
                "{",
                "	PrimaryActorTick.bCanEverTick = false;",
                "}",
            ])

    emit_ue_class(cls_name(0), "AActor", "GameFramework/Actor.h")

    for i in range(1, depth):
        emit_ue_class(cls_name(i), cls_name(i-1), f"{cls_name(i-1)}.h")


def gen(name_base: str, depth: int, output: pathlib.Path):

    LOG.info("Emitting myrtti classes...")
    emit_myrtti(name_base, depth, output)
    LOG.info("Emitting UE classes...")
    emit_ue(name_base, depth, output)
    LOG.info("Done.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--name-base", help="Base for classes naming"
    )
    parser.add_argument(
        "--depth", help="Hierarchy depth", type=int
    )
    parser.add_argument(
        "--output", help="Output path, where classes will be stored", type=pathlib.Path
    )

    args = parser.parse_args()

    gen(args.name_base, args.depth, args.output)
