/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/


#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/


#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
typedef void (*funcp)(char *, char *);
extern int main(int, char**);
extern void execute_25(char*, char *);
extern void execute_26(char*, char *);
extern void execute_27(char*, char *);
extern void execute_28(char*, char *);
extern void execute_29(char*, char *);
extern void execute_30(char*, char *);
extern void execute_7098(char*, char *);
extern void execute_7099(char*, char *);
extern void execute_72(char*, char *);
extern void execute_73(char*, char *);
extern void execute_74(char*, char *);
extern void execute_75(char*, char *);
extern void execute_76(char*, char *);
extern void execute_77(char*, char *);
extern void execute_78(char*, char *);
extern void execute_79(char*, char *);
extern void execute_80(char*, char *);
extern void execute_81(char*, char *);
extern void execute_82(char*, char *);
extern void execute_83(char*, char *);
extern void execute_84(char*, char *);
extern void execute_85(char*, char *);
extern void execute_86(char*, char *);
extern void execute_7095(char*, char *);
extern void execute_7096(char*, char *);
extern void execute_7097(char*, char *);
extern void execute_88(char*, char *);
extern void execute_89(char*, char *);
extern void execute_90(char*, char *);
extern void execute_92(char*, char *);
extern void execute_93(char*, char *);
extern void execute_94(char*, char *);
extern void execute_95(char*, char *);
extern void execute_96(char*, char *);
extern void execute_97(char*, char *);
extern void execute_98(char*, char *);
extern void execute_99(char*, char *);
extern void execute_100(char*, char *);
extern void execute_101(char*, char *);
extern void execute_102(char*, char *);
extern void execute_103(char*, char *);
extern void execute_105(char*, char *);
extern void execute_106(char*, char *);
extern void execute_111(char*, char *);
extern void execute_108(char*, char *);
extern void execute_109(char*, char *);
extern void execute_110(char*, char *);
extern void execute_3254(char*, char *);
extern void execute_123(char*, char *);
extern void execute_124(char*, char *);
extern void execute_136(char*, char *);
extern void execute_137(char*, char *);
extern void execute_138(char*, char *);
extern void execute_139(char*, char *);
extern void execute_140(char*, char *);
extern void execute_178(char*, char *);
extern void execute_142(char*, char *);
extern void execute_145(char*, char *);
extern void execute_169(char*, char *);
extern void execute_170(char*, char *);
extern void execute_151(char*, char *);
extern void execute_153(char*, char *);
extern void execute_155(char*, char *);
extern void execute_157(char*, char *);
extern void execute_159(char*, char *);
extern void execute_161(char*, char *);
extern void execute_163(char*, char *);
extern void execute_165(char*, char *);
extern void execute_167(char*, char *);
extern void execute_177(char*, char *);
extern void execute_173(char*, char *);
extern void execute_175(char*, char *);
extern void execute_197(char*, char *);
extern void execute_198(char*, char *);
extern void execute_199(char*, char *);
extern void execute_200(char*, char *);
extern void execute_201(char*, char *);
extern void execute_202(char*, char *);
extern void execute_203(char*, char *);
extern void execute_204(char*, char *);
extern void execute_205(char*, char *);
extern void execute_206(char*, char *);
extern void execute_207(char*, char *);
extern void execute_208(char*, char *);
extern void execute_209(char*, char *);
extern void execute_210(char*, char *);
extern void execute_211(char*, char *);
extern void execute_212(char*, char *);
extern void execute_213(char*, char *);
extern void execute_214(char*, char *);
extern void execute_215(char*, char *);
extern void execute_216(char*, char *);
extern void execute_217(char*, char *);
extern void execute_218(char*, char *);
extern void execute_219(char*, char *);
extern void execute_220(char*, char *);
extern void execute_221(char*, char *);
extern void execute_222(char*, char *);
extern void execute_223(char*, char *);
extern void execute_224(char*, char *);
extern void execute_225(char*, char *);
extern void execute_226(char*, char *);
extern void execute_227(char*, char *);
extern void execute_228(char*, char *);
extern void execute_229(char*, char *);
extern void execute_230(char*, char *);
extern void execute_231(char*, char *);
extern void execute_232(char*, char *);
extern void execute_233(char*, char *);
extern void execute_234(char*, char *);
extern void execute_235(char*, char *);
extern void execute_236(char*, char *);
extern void execute_237(char*, char *);
extern void execute_238(char*, char *);
extern void execute_239(char*, char *);
extern void execute_240(char*, char *);
extern void execute_241(char*, char *);
extern void execute_242(char*, char *);
extern void execute_243(char*, char *);
extern void execute_244(char*, char *);
extern void execute_245(char*, char *);
extern void execute_246(char*, char *);
extern void execute_247(char*, char *);
extern void execute_248(char*, char *);
extern void execute_249(char*, char *);
extern void execute_250(char*, char *);
extern void execute_251(char*, char *);
extern void execute_252(char*, char *);
extern void execute_253(char*, char *);
extern void execute_254(char*, char *);
extern void execute_255(char*, char *);
extern void execute_256(char*, char *);
extern void execute_257(char*, char *);
extern void execute_258(char*, char *);
extern void execute_259(char*, char *);
extern void execute_260(char*, char *);
extern void execute_261(char*, char *);
extern void execute_262(char*, char *);
extern void execute_263(char*, char *);
extern void execute_264(char*, char *);
extern void execute_265(char*, char *);
extern void execute_266(char*, char *);
extern void execute_267(char*, char *);
extern void execute_268(char*, char *);
extern void execute_269(char*, char *);
extern void execute_270(char*, char *);
extern void execute_271(char*, char *);
extern void execute_272(char*, char *);
extern void execute_273(char*, char *);
extern void execute_274(char*, char *);
extern void execute_275(char*, char *);
extern void execute_276(char*, char *);
extern void execute_277(char*, char *);
extern void execute_278(char*, char *);
extern void execute_279(char*, char *);
extern void execute_280(char*, char *);
extern void execute_281(char*, char *);
extern void execute_282(char*, char *);
extern void execute_283(char*, char *);
extern void execute_284(char*, char *);
extern void execute_285(char*, char *);
extern void execute_286(char*, char *);
extern void execute_287(char*, char *);
extern void execute_288(char*, char *);
extern void execute_289(char*, char *);
extern void execute_290(char*, char *);
extern void execute_291(char*, char *);
extern void execute_292(char*, char *);
extern void execute_293(char*, char *);
extern void execute_294(char*, char *);
extern void execute_295(char*, char *);
extern void execute_296(char*, char *);
extern void execute_297(char*, char *);
extern void execute_298(char*, char *);
extern void execute_299(char*, char *);
extern void execute_300(char*, char *);
extern void execute_301(char*, char *);
extern void execute_302(char*, char *);
extern void execute_303(char*, char *);
extern void execute_304(char*, char *);
extern void execute_305(char*, char *);
extern void execute_306(char*, char *);
extern void execute_307(char*, char *);
extern void execute_308(char*, char *);
extern void execute_309(char*, char *);
extern void execute_310(char*, char *);
extern void execute_311(char*, char *);
extern void execute_312(char*, char *);
extern void execute_313(char*, char *);
extern void execute_314(char*, char *);
extern void execute_315(char*, char *);
extern void execute_316(char*, char *);
extern void execute_317(char*, char *);
extern void execute_318(char*, char *);
extern void execute_319(char*, char *);
extern void execute_320(char*, char *);
extern void execute_321(char*, char *);
extern void execute_322(char*, char *);
extern void execute_323(char*, char *);
extern void execute_324(char*, char *);
extern void execute_325(char*, char *);
extern void execute_326(char*, char *);
extern void execute_3305(char*, char *);
extern void execute_3258(char*, char *);
extern void execute_6428(char*, char *);
extern void execute_3309(char*, char *);
extern void execute_3310(char*, char *);
extern void execute_6479(char*, char *);
extern void execute_7067(char*, char *);
extern void execute_6483(char*, char *);
extern void execute_6484(char*, char *);
extern void execute_7079(char*, char *);
extern void execute_7081(char*, char *);
extern void execute_7085(char*, char *);
extern void execute_7086(char*, char *);
extern void execute_7087(char*, char *);
extern void execute_7088(char*, char *);
extern void execute_7089(char*, char *);
extern void execute_7090(char*, char *);
extern void execute_7091(char*, char *);
extern void execute_7092(char*, char *);
extern void execute_7084(char*, char *);
extern void execute_7094(char*, char *);
extern void vhdl_transfunc_eventcallback(char*, char*, unsigned, unsigned, unsigned, char *);
extern void transaction_10(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_16(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_72(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_216(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_463(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_710(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_957(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_1204(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_1451(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_1698(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_1945(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_2192(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_2439(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_2686(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_2933(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_3180(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_3427(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_3674(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_3921(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_4188(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_4435(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_4682(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_4929(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_5176(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_5423(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_5670(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_5917(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_6164(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_6411(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_6658(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_6905(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_7152(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_7399(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_7646(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_7893(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_8160(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_8407(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_8654(char*, char*, unsigned, unsigned, unsigned);
funcp funcTab[262] = {(funcp)execute_25, (funcp)execute_26, (funcp)execute_27, (funcp)execute_28, (funcp)execute_29, (funcp)execute_30, (funcp)execute_7098, (funcp)execute_7099, (funcp)execute_72, (funcp)execute_73, (funcp)execute_74, (funcp)execute_75, (funcp)execute_76, (funcp)execute_77, (funcp)execute_78, (funcp)execute_79, (funcp)execute_80, (funcp)execute_81, (funcp)execute_82, (funcp)execute_83, (funcp)execute_84, (funcp)execute_85, (funcp)execute_86, (funcp)execute_7095, (funcp)execute_7096, (funcp)execute_7097, (funcp)execute_88, (funcp)execute_89, (funcp)execute_90, (funcp)execute_92, (funcp)execute_93, (funcp)execute_94, (funcp)execute_95, (funcp)execute_96, (funcp)execute_97, (funcp)execute_98, (funcp)execute_99, (funcp)execute_100, (funcp)execute_101, (funcp)execute_102, (funcp)execute_103, (funcp)execute_105, (funcp)execute_106, (funcp)execute_111, (funcp)execute_108, (funcp)execute_109, (funcp)execute_110, (funcp)execute_3254, (funcp)execute_123, (funcp)execute_124, (funcp)execute_136, (funcp)execute_137, (funcp)execute_138, (funcp)execute_139, (funcp)execute_140, (funcp)execute_178, (funcp)execute_142, (funcp)execute_145, (funcp)execute_169, (funcp)execute_170, (funcp)execute_151, (funcp)execute_153, (funcp)execute_155, (funcp)execute_157, (funcp)execute_159, (funcp)execute_161, (funcp)execute_163, (funcp)execute_165, (funcp)execute_167, (funcp)execute_177, (funcp)execute_173, (funcp)execute_175, (funcp)execute_197, (funcp)execute_198, (funcp)execute_199, (funcp)execute_200, (funcp)execute_201, (funcp)execute_202, (funcp)execute_203, (funcp)execute_204, (funcp)execute_205, (funcp)execute_206, (funcp)execute_207, (funcp)execute_208, (funcp)execute_209, (funcp)execute_210, (funcp)execute_211, (funcp)execute_212, (funcp)execute_213, (funcp)execute_214, (funcp)execute_215, (funcp)execute_216, (funcp)execute_217, (funcp)execute_218, (funcp)execute_219, (funcp)execute_220, (funcp)execute_221, (funcp)execute_222, (funcp)execute_223, (funcp)execute_224, (funcp)execute_225, (funcp)execute_226, (funcp)execute_227, (funcp)execute_228, (funcp)execute_229, (funcp)execute_230, (funcp)execute_231, (funcp)execute_232, (funcp)execute_233, (funcp)execute_234, (funcp)execute_235, (funcp)execute_236, (funcp)execute_237, (funcp)execute_238, (funcp)execute_239, (funcp)execute_240, (funcp)execute_241, (funcp)execute_242, (funcp)execute_243, (funcp)execute_244, (funcp)execute_245, (funcp)execute_246, (funcp)execute_247, (funcp)execute_248, (funcp)execute_249, (funcp)execute_250, (funcp)execute_251, (funcp)execute_252, (funcp)execute_253, (funcp)execute_254, (funcp)execute_255, (funcp)execute_256, (funcp)execute_257, (funcp)execute_258, (funcp)execute_259, (funcp)execute_260, (funcp)execute_261, (funcp)execute_262, (funcp)execute_263, (funcp)execute_264, (funcp)execute_265, (funcp)execute_266, (funcp)execute_267, (funcp)execute_268, (funcp)execute_269, (funcp)execute_270, (funcp)execute_271, (funcp)execute_272, (funcp)execute_273, (funcp)execute_274, (funcp)execute_275, (funcp)execute_276, (funcp)execute_277, (funcp)execute_278, (funcp)execute_279, (funcp)execute_280, (funcp)execute_281, (funcp)execute_282, (funcp)execute_283, (funcp)execute_284, (funcp)execute_285, (funcp)execute_286, (funcp)execute_287, (funcp)execute_288, (funcp)execute_289, (funcp)execute_290, (funcp)execute_291, (funcp)execute_292, (funcp)execute_293, (funcp)execute_294, (funcp)execute_295, (funcp)execute_296, (funcp)execute_297, (funcp)execute_298, (funcp)execute_299, (funcp)execute_300, (funcp)execute_301, (funcp)execute_302, (funcp)execute_303, (funcp)execute_304, (funcp)execute_305, (funcp)execute_306, (funcp)execute_307, (funcp)execute_308, (funcp)execute_309, (funcp)execute_310, (funcp)execute_311, (funcp)execute_312, (funcp)execute_313, (funcp)execute_314, (funcp)execute_315, (funcp)execute_316, (funcp)execute_317, (funcp)execute_318, (funcp)execute_319, (funcp)execute_320, (funcp)execute_321, (funcp)execute_322, (funcp)execute_323, (funcp)execute_324, (funcp)execute_325, (funcp)execute_326, (funcp)execute_3305, (funcp)execute_3258, (funcp)execute_6428, (funcp)execute_3309, (funcp)execute_3310, (funcp)execute_6479, (funcp)execute_7067, (funcp)execute_6483, (funcp)execute_6484, (funcp)execute_7079, (funcp)execute_7081, (funcp)execute_7085, (funcp)execute_7086, (funcp)execute_7087, (funcp)execute_7088, (funcp)execute_7089, (funcp)execute_7090, (funcp)execute_7091, (funcp)execute_7092, (funcp)execute_7084, (funcp)execute_7094, (funcp)vhdl_transfunc_eventcallback, (funcp)transaction_10, (funcp)transaction_16, (funcp)transaction_72, (funcp)transaction_216, (funcp)transaction_463, (funcp)transaction_710, (funcp)transaction_957, (funcp)transaction_1204, (funcp)transaction_1451, (funcp)transaction_1698, (funcp)transaction_1945, (funcp)transaction_2192, (funcp)transaction_2439, (funcp)transaction_2686, (funcp)transaction_2933, (funcp)transaction_3180, (funcp)transaction_3427, (funcp)transaction_3674, (funcp)transaction_3921, (funcp)transaction_4188, (funcp)transaction_4435, (funcp)transaction_4682, (funcp)transaction_4929, (funcp)transaction_5176, (funcp)transaction_5423, (funcp)transaction_5670, (funcp)transaction_5917, (funcp)transaction_6164, (funcp)transaction_6411, (funcp)transaction_6658, (funcp)transaction_6905, (funcp)transaction_7152, (funcp)transaction_7399, (funcp)transaction_7646, (funcp)transaction_7893, (funcp)transaction_8160, (funcp)transaction_8407, (funcp)transaction_8654};
const int NumRelocateId= 262;

void relocate(char *dp)
{
	iki_relocate(dp, "xsim.dir/main_test_behav/xsim.reloc",  (void **)funcTab, 262);
	iki_vhdl_file_variable_register(dp + 1975496);
	iki_vhdl_file_variable_register(dp + 1975552);


	/*Populate the transaction function pointer field in the whole net structure */
}

void sensitize(char *dp)
{
	iki_sensitize(dp, "xsim.dir/main_test_behav/xsim.reloc");
}

	// Initialize Verilog nets in mixed simulation, for the cases when the value at time 0 should be propagated from the mixed language Vhdl net

void simulate(char *dp)
{
		iki_schedule_processes_at_time_zero(dp, "xsim.dir/main_test_behav/xsim.reloc");

	iki_execute_processes();

	// Schedule resolution functions for the multiply driven Verilog nets that have strength
	// Schedule transaction functions for the singly driven Verilog nets that have strength

}
#include "iki_bridge.h"
void relocate(char *);

void sensitize(char *);

void simulate(char *);

extern SYSTEMCLIB_IMP_DLLSPEC void local_register_implicit_channel(int, char*);
extern void implicit_HDL_SCinstatiate();

extern SYSTEMCLIB_IMP_DLLSPEC int xsim_argc_copy ;
extern SYSTEMCLIB_IMP_DLLSPEC char** xsim_argv_copy ;

int main(int argc, char **argv)
{
    iki_heap_initialize("ms", "isimmm", 0, 2147483648) ;
    iki_set_sv_type_file_path_name("xsim.dir/main_test_behav/xsim.svtype");
    iki_set_crvs_dump_file_path_name("xsim.dir/main_test_behav/xsim.crvsdump");
    void* design_handle = iki_create_design("xsim.dir/main_test_behav/xsim.mem", (void *)relocate, (void *)sensitize, (void *)simulate, 0, isimBridge_getWdbWriter(), 0, argc, argv);
     iki_set_rc_trial_count(100);
    (void) design_handle;
    return iki_simulate_design();
}
