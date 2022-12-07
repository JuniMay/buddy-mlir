//===-- RISCVSubtarget.h - Define Subtarget for the RISCV -------*- C++ -*-===//
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//===----------------------------------------------------------------------===//
//
// This file declares the RISCV specific subclass of TargetSubtargetInfo.
// This file includes the buddy extension subtarget.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_RISCV_RISCVSUBTARGET_H
#define LLVM_LIB_TARGET_RISCV_RISCVSUBTARGET_H

#include "MCTargetDesc/RISCVBaseInfo.h"
#include "RISCVFrameLowering.h"
#include "RISCVISelLowering.h"
#include "RISCVInstrInfo.h"
#include "llvm/CodeGen/GlobalISel/CallLowering.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"
#include "llvm/CodeGen/GlobalISel/LegalizerInfo.h"
#include "llvm/CodeGen/RegisterBankInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"
#include <iostream>

#define GET_SUBTARGETINFO_HEADER
#include "RISCVGenSubtargetInfo.inc"

namespace llvm {
class StringRef;

class RISCVSubtarget : public RISCVGenSubtargetInfo {
public:
  enum RISCVProcFamilyEnum : uint8_t {
    Others,
    SiFive7,
  };

private:
  virtual void anchor();

  RISCVProcFamilyEnum RISCVProcFamily = Others;

  bool HasBuddyExt = false;
  bool HasStdExtM = false;
  bool HasStdExtA = false;
  bool HasStdExtF = false;
  bool HasStdExtD = false;
  bool HasStdExtC = false;
  bool HasStdExtZihintpause = false;
  bool HasStdExtZihintntl = false;
  bool HasStdExtZba = false;
  bool HasStdExtZbb = false;
  bool HasStdExtZbc = false;
  bool HasStdExtZbs = false;
  bool HasStdExtZca = false;
  bool HasStdExtZcd = false;
  bool HasStdExtZcf = false;
  bool HasStdExtV = false;
  bool HasStdExtZve32x = false;
  bool HasStdExtZve32f = false;
  bool HasStdExtZve64x = false;
  bool HasStdExtZve64f = false;
  bool HasStdExtZve64d = false;
  bool HasStdExtZvfh = false;
  bool HasStdExtZfhmin = false;
  bool HasStdExtZfh = false;
  bool HasStdExtZfinx = false;
  bool HasStdExtZdinx = false;
  bool HasStdExtZhinxmin = false;
  bool HasStdExtZhinx = false;
  bool HasStdExtZbkb = false;
  bool HasStdExtZbkc = false;
  bool HasStdExtZbkx = false;
  bool HasStdExtZknd = false;
  bool HasStdExtZkne = false;
  bool HasStdExtZknh = false;
  bool HasStdExtZksed = false;
  bool HasStdExtZksh = false;
  bool HasStdExtZkr = false;
  bool HasStdExtZkn = false;
  bool HasStdExtZks = false;
  bool HasStdExtZkt = false;
  bool HasStdExtZk = false;
  bool HasStdExtZicbom = false;
  bool HasStdExtZicboz = false;
  bool HasStdExtZicbop = false;
  bool HasStdExtSvnapot = false;
  bool HasStdExtSvinval = false;
  bool HasStdExtZmmul = false;
  bool HasStdExtZawrs = false;
  bool HasStdExtZtso = false;
  bool HasVendorXVentanaCondOps = false;
  bool HasRV32 = false;
  bool HasRV64 = false;
  bool IsRV32E = false;
  bool EnableLinkerRelax = false;
  bool EnableRVCHintInstrs = true;
  bool EnableDefaultUnroll = true;
  bool EnableSaveRestore = false;
  bool EnableUnalignedScalarMem = false;
  bool HasShortForwardBranchOpt = false;
  bool HasLUIADDIFusion = false;
  bool HasForcedAtomics = false;
  bool HasOptimizedZeroStrideLoad = true;
  unsigned XLen = 32;
  unsigned ZvlLen = 0;
  MVT XLenVT = MVT::i32;
  uint8_t MaxInterleaveFactor = 2;
  RISCVABI::ABI TargetABI = RISCVABI::ABI_Unknown;
  std::bitset<RISCV::NUM_TARGET_REGS> UserReservedRegister;
  RISCVFrameLowering FrameLowering;
  RISCVInstrInfo InstrInfo;
  RISCVRegisterInfo RegInfo;
  RISCVTargetLowering TLInfo;
  SelectionDAGTargetInfo TSInfo;

  /// Initializes using the passed in CPU and feature strings so that we can
  /// use initializer lists for subtarget initialization.
  RISCVSubtarget &initializeSubtargetDependencies(const Triple &TT,
                                                  StringRef CPU,
                                                  StringRef TuneCPU,
                                                  StringRef FS,
                                                  StringRef ABIName);

public:
  // Initializes the data members to match that of the specified triple.
  RISCVSubtarget(const Triple &TT, StringRef CPU, StringRef TuneCPU,
                 StringRef FS, StringRef ABIName, const TargetMachine &TM);

  // Parses features string setting specified subtarget options. The
  // definition of this function is auto-generated by tblgen.
  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);

  const RISCVFrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }
  const RISCVInstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const RISCVRegisterInfo *getRegisterInfo() const override {
    return &RegInfo;
  }
  const RISCVTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }
  const SelectionDAGTargetInfo *getSelectionDAGInfo() const override {
    return &TSInfo;
  }
  bool enableMachineScheduler() const override { return true; }

  /// Returns RISCV processor family.
  /// Avoid this function! CPU specifics should be kept local to this class
  /// and preferably modeled with SubtargetFeatures or properties in
  /// initializeProperties().
  RISCVProcFamilyEnum getProcFamily() const { return RISCVProcFamily; }

  bool hasBuddyExt() const {return HasBuddyExt; }
  bool hasStdExtM() const { return HasStdExtM; }
  bool hasStdExtA() const { return HasStdExtA; }
  bool hasStdExtF() const { return HasStdExtF; }
  bool hasStdExtD() const { return HasStdExtD; }
  bool hasStdExtC() const { return HasStdExtC; }
  bool hasStdExtCOrZca() const { return HasStdExtC || HasStdExtZca; }
  bool hasStdExtV() const { return HasStdExtV; }
  bool hasStdExtZihintpause() const { return HasStdExtZihintpause; }
  bool hasStdExtZihintntl() const { return HasStdExtZihintntl; }
  bool hasStdExtZba() const { return HasStdExtZba; }
  bool hasStdExtZbb() const { return HasStdExtZbb; }
  bool hasStdExtZbc() const { return HasStdExtZbc; }
  bool hasStdExtZbs() const { return HasStdExtZbs; }
  bool hasStdExtZca() const { return HasStdExtZca; }
  bool hasStdExtZcd() const { return HasStdExtZcd; }
  bool hasStdExtZcf() const { return HasStdExtZcf; }
  bool hasStdExtZvl() const { return ZvlLen != 0; }
  bool hasStdExtZvfh() const { return HasStdExtZvfh; }
  bool hasStdExtZfhmin() const { return HasStdExtZfhmin; }
  bool hasStdExtZfh() const { return HasStdExtZfh; }
  bool hasStdExtZfinx() const { return HasStdExtZfinx; }
  bool hasStdExtZdinx() const { return HasStdExtZdinx; }
  bool hasStdExtZhinxmin() const { return HasStdExtZhinxmin; }
  bool hasStdExtZhinx() const { return HasStdExtZhinx; }
  bool hasStdExtZbkb() const { return HasStdExtZbkb; }
  bool hasStdExtZbkc() const { return HasStdExtZbkc; }
  bool hasStdExtZbkx() const { return HasStdExtZbkx; }
  bool hasStdExtZknd() const { return HasStdExtZknd; }
  bool hasStdExtZkne() const { return HasStdExtZkne; }
  bool hasStdExtZknh() const { return HasStdExtZknh; }
  bool hasStdExtZksed() const { return HasStdExtZksed; }
  bool hasStdExtZksh() const { return HasStdExtZksh; }
  bool hasStdExtZkr() const { return HasStdExtZkr; }
  bool hasStdExtZicbom() const { return HasStdExtZicbom; }
  bool hasStdExtZicboz() const { return HasStdExtZicboz; }
  bool hasStdExtZicbop() const { return HasStdExtZicbop; }
  bool hasStdExtSvnapot() const { return HasStdExtSvnapot; }
  bool hasStdExtSvinval() const { return HasStdExtSvinval; }
  bool hasStdExtZawrs() const { return HasStdExtZawrs; }
  bool hasStdExtZmmul() const { return HasStdExtZmmul; }
  bool hasStdExtZtso() const { return HasStdExtZtso; }
  bool hasVendorXVentanaCondOps() const { return HasVendorXVentanaCondOps; }
  bool is64Bit() const { return HasRV64; }
  bool isRV32E() const { return IsRV32E; }
  bool enableLinkerRelax() const { return EnableLinkerRelax; }
  bool enableRVCHintInstrs() const { return EnableRVCHintInstrs; }
  bool enableDefaultUnroll() const { return EnableDefaultUnroll; }
  bool enableSaveRestore() const { return EnableSaveRestore; }
  bool hasShortForwardBranchOpt() const { return HasShortForwardBranchOpt; }
  bool enableUnalignedScalarMem() const { return EnableUnalignedScalarMem; }
  bool hasLUIADDIFusion() const { return HasLUIADDIFusion; }
  bool hasForcedAtomics() const { return HasForcedAtomics; }
  bool hasOptimizedZeroStrideLoad() const { return HasOptimizedZeroStrideLoad; }
  MVT getXLenVT() const { return XLenVT; }
  unsigned getXLen() const { return XLen; }
  unsigned getFLen() const {
    if (HasStdExtD)
      return 64;

    if (HasStdExtF)
      return 32;

    return 0;
  }
  unsigned getELEN() const {
    assert(hasVInstructions() && "Expected V extension");
    return hasVInstructionsI64() ? 64 : 32;
  }
  unsigned getRealMinVLen() const {
    unsigned VLen = getMinRVVVectorSizeInBits();
    return VLen == 0 ? getArchMinVLen() : VLen;
  }
  unsigned getRealMaxVLen() const {
    unsigned VLen = getMaxRVVVectorSizeInBits();
    return VLen == 0 ? getArchMaxVLen() : VLen;
  }
  RISCVABI::ABI getTargetABI() const { return TargetABI; }
  bool isRegisterReservedByUser(Register i) const {
    assert(i < RISCV::NUM_TARGET_REGS && "Register out of range");
    return UserReservedRegister[i];
  }

  bool hasMacroFusion() const { return hasLUIADDIFusion(); }

  // Vector codegen related methods.
  bool hasVInstructions() const { return HasStdExtZve32x; }
  bool hasVInstructionsI64() const { return HasStdExtZve64x; }
  bool hasVInstructionsF16() const { return HasStdExtZvfh && HasStdExtZfh; }
  // FIXME: Consider Zfinx in the future
  bool hasVInstructionsF32() const { return HasStdExtZve32f && HasStdExtF; }
  // FIXME: Consider Zdinx in the future
  bool hasVInstructionsF64() const { return HasStdExtZve64d && HasStdExtD; }
  // F16 and F64 both require F32.
  bool hasVInstructionsAnyF() const { return hasVInstructionsF32(); }
  unsigned getMaxInterleaveFactor() const {
    return hasVInstructions() ? MaxInterleaveFactor : 1;
  }

protected:
  // GlobalISel related APIs.
  std::unique_ptr<CallLowering> CallLoweringInfo;
  std::unique_ptr<InstructionSelector> InstSelector;
  std::unique_ptr<LegalizerInfo> Legalizer;
  std::unique_ptr<RegisterBankInfo> RegBankInfo;

  // Return the known range for the bit length of RVV data registers as set
  // at the command line. A value of 0 means nothing is known about that particular
  // limit beyond what's implied by the architecture.
  // NOTE: Please use getRealMinVLen and getRealMaxVLen instead!
  unsigned getMaxRVVVectorSizeInBits() const;
  unsigned getMinRVVVectorSizeInBits() const;

  // Return the known range for the bit length of RVV data registers as indicated
  // by -march and -mattr.
  unsigned getArchMinVLen() const { return ZvlLen; }
  unsigned getArchMaxVLen() const { return 65536; }

public:
  const CallLowering *getCallLowering() const override;
  InstructionSelector *getInstructionSelector() const override;
  const LegalizerInfo *getLegalizerInfo() const override;
  const RegisterBankInfo *getRegBankInfo() const override;

  bool useConstantPoolForLargeInts() const;

  // Maximum cost used for building integers, integers will be put into constant
  // pool if exceeded.
  unsigned getMaxBuildIntsCost() const;

  unsigned getMaxLMULForFixedLengthVectors() const;
  bool useRVVForFixedLengthVectors() const;

  bool enableSubRegLiveness() const override;

  void getPostRAMutations(std::vector<std::unique_ptr<ScheduleDAGMutation>>
                              &Mutations) const override;
};
} // End llvm namespace

#endif
