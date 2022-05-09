

Dcm = Module(moduleName="Dcm")
Dcm_CFG_H_Obj,Dcm_LCFG_H_Obj,Dcm_LCFG_C_Obj = Dcm.getFileObjects()

Dcm_CFG_H_Obj.writeNewLine(numberLines=2)

Dcm_CFG_H_Obj.createMacro(macroPath="Dcm.DcmConfigSet.DcmDsp",
						instanceIndex=0,
						parameterShortName="DcmDspMaxDidToRead",
						macroShortName=None,
						numberTabs=5)

Dcm_CFG_H_Obj.writeNewLine(numberLines=2)


Dcm_CFG_H_Obj.createMultipleMacro(containerPath="Dcm.DcmConfigSet.DcmDsp",
								   parameter="DcmDspMaxDidToRead",
								   parameterShortName=None,
								   numberTabs=5)

Dcm_CFG_H_Obj.writeNewLine(numberLines=2)

DcmDsp_parametersList="All"
DcmDsp_referencesList="All"
DcmDsp_containersIndexList="All"
DcmDsp_subContainersList={"All":"NotConc"}

Dcm_LCFG_C_Obj.createStruct(structPath="Dcm.DcmConfigSet.DcmDsp",
							 parametersList=DcmDsp_parametersList,
							 referencesList=DcmDsp_referencesList,
							 containersIndexList=DcmDsp_containersIndexList,
							 subContainersList=DcmDsp_subContainersList)


Dcm.close()













