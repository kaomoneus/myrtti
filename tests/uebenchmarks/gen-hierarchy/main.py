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
            f"with_rtti_root(struct, {cls_name(0)})",
            "with_rtti_end();",
            "",
        ])

        for i in range(1, depth):
            LOG.info(f"    myrtti:    writing {cls_name(i)}")
            _lines(f, [
                f"with_rtti(struct, {cls_name(i)}, {cls_name(i-1)})",
                "with_rtti_end();",
                "",
            ])


def emit_ue(name_base: str, depth: int, output: pathlib.Path):

    def cls_name(d: int):
        return f"UUnreal_{name_base}_{d}"

    def emit_ue_class(name: str, parent: str, parent_header: str = None):
        header = output / f"{name}.h"
        cpp = output / f"{name}.cpp"
        with open(header, "w") as f:
            LOG.info(f"    ue:    writing {header}")
            _lines(f, [
                    "#pragma once",
                    "",
                    "#include \"CoreMinimal.h\"",
                    f"#include \"{parent_header}\"" if parent_header else "",
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
                "	// PrimaryActorTick.bCanEverTick = false;",
                "}",
            ])

    emit_ue_class(cls_name(0), "UObject")

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
