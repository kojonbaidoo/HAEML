/*
Input Layer
Hidden Layer
Output Layer
Non-linearity
    Softmax
    Relu
*/

/*
ARCHITECTURE
L0 3: INPUT LAYER
L1 16: HIDDEN LAYER
L2 16: HIDDEN LAYER
L3 3: Output LAYER
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define INPUT_LAYER 3
#define L1_LAYER 16
#define L2_LAYER 16
#define L3_LAYER 3

#define L1_WEIGHT_ROW 16
#define L1_WEIGHT_COL 3
#define L1_BIAS_COUNT 16

#define L2_WEIGHT_ROW 16
#define L2_WEIGHT_COL 16
#define L2_BIAS_COUNT 16

#define L3_WEIGHT_ROW 3
#define L3_WEIGHT_COL 16
#define L3_BIAS_COUNT 3

double L1_WEIGHTS[L1_WEIGHT_ROW][L1_WEIGHT_COL] = {
    {-0.446940159565331,0.0503051742020588,0.895000661431211},
    {0.272376518427189,0.529389059425728,1.91844527775307},
    {-0.805133871867814,-2.66255388542537,-0.774221243724805},
    {-0.474341747695588,0.784184866128361,-1.29021967656508},
    {-0.594756433247355,1.25810757182344,-0.174527172645466},
    {-2.35092788714498,-1.33101862652572,0.732893908572609},
    {-0.852944632872311,1.06130723627218,1.64880325552852},
    {0.23815943315168,0.868827144008632,-2.82015153278886},
    {0.255072415871753,-0.566061085550702,-0.182629058241287},
    {1.80047244756103,-0.800898129760995,-0.935690479211973},
    {-1.18692626353998,2.31366882500829,-1.05934080639216},
    {0.71654462113921,-0.215453067030168,-0.357226894113805},
    {1.74237814237155,1.08740016279188,-1.37880773958601},
    {0.0897144360751598,0.0999463305426775,-0.2121376497116},
    {-0.155182701356012,0.143644397197579,0.361872334644592},
    {1.95564857652032,-0.269982567647195,2.52074828831962},
};

double L1_BIAS[L1_BIAS_COUNT] = {-0.526462055302771,
    0.502184837564316,
    0.0774149774038273,
    1.01486657995262,
    0.385183692290811,
    1.05833353822702,
    -0.443033245977843,
    1.60684136239646,
    -0.44537662031255,
    0.741677272839251,
    1.07553634064502,
    -0.379414610229653,
    0.902570632134698,
    0.763572258831601,
    -0.59163745231196,
    -0.169414691402274,
};

double L2_WEIGHTS[L2_WEIGHT_ROW][L2_WEIGHT_COL] = {
    {-0.191484236554705,-0.563807914120118,1.2297278967416,1.03103904551214,-0.82761387401679,0.93945632386128,0.0944551329911518,-0.200892932358581,-0.410430800540764,-0.451256257621061,-0.299423978293865,0.0719809826410677,-0.828640002588641,0.663672633570311,-0.482887367122389,-0.701473637087828},
    {-0.382827298461635,1.7849005692076,0.392924499102983,-0.890607105773752,0.205982879743277,-1.04571394191714,1.74430131776591,-1.46217384496773,-0.543132846689938,-0.00417061045237551,-1.28825054422564,0.539552112379671,0.0878289119254004,0.639914330901471,-0.983284255583939,2.29153466413945},
    {-0.990854821746329,-0.600359282237375,-0.82216572596066,-0.439550511329487,-0.253031851783709,-0.137660843739404,-0.465720474257123,0.396977498450231,0.784845434098563,-0.822580039683333,-0.685732730459155,0.549372524770778,0.581752939601449,-0.405961599527097,-0.0719939482381062,0.146285248240175},
    {0.00668288588965629,-0.659578750711646,0.0505515049292857,-0.559076122441814,0.14027752620382,1.61686843605944,-0.358233352962655,-0.236473880874895,0.1026166323278,-0.0330443541206239,0.32650796486435,0.512599678047568,-0.918052495073253,0.715026030561059,-0.707677959215506,-1.13439823391499},
    {0.744343255822373,0.162743440702629,0.0983917073213002,-0.907831093627052,-0.346998019472042,0.713883430158192,-0.636737241498687,-0.787941541951337,-0.248359655669357,-0.395571679101402,-0.447571200201225,0.229428053260136,-0.426996400538873,-0.40165911800544,-0.550961850704571,-0.9230442913555},
    {-0.652175852379715,-0.839320525678303,1.84002363700893,0.578763217519302,0.380371021513626,0.965693970701341,0.541224970063016,-1.00629501607508,-0.256338356335916,-0.816909489337103,0.806597267620027,0.672243042250944,-1.04477030333257,0.306034260173476,-0.928283634123306,-1.45578662111387},
    {-0.214397481181533,0.835967130669437,-0.485395685232615,-0.980233314115568,0.437899307242546,-0.998590664970257,-0.136891237111742,0.126793432335047,0.810173609211111,-0.560927536282776,-0.761881508360997,-0.448203415652995,0.716793232491993,-0.00635770289426536,0.885078473779911,0.680837410774052},
    {0.300029998267219,0.0342169394155577,0.94125577130858,0.621553869215724,-0.354545913739466,1.25315496631887,1.12207758410899,0.783843230473979,-0.61143699940945,0.227475432262295,-0.347832131097802,-0.0688947172181545,0.528787665908071,0.277829175782754,-0.332155792085698,-0.472930349654633},
    {-0.897247780185256,0.199644973288948,-0.351676970527174,0.851112788905274,0.0259035860015268,-0.493564302948042,0.441722969792257,-0.204614027500226,-0.43618240964146,-1.18348436698191,1.60918371099431,-0.315387424795334,1.14736126877402,-0.460663071697427,0.721406284788295,-0.514337433325259},
    {-0.61909333777272,-0.27499393137907,1.13626142269136,0.22707857842756,-1.00382529815741,-0.644921743575788,-0.723192450060928,-0.463016940640224,0.30073790200547,1.80037738728189,-0.948848038227536,0.0280267688601014,1.02834694869904,-0.0346597627144842,-0.999374497950813,0.697986388195099},
    {-0.69549617059207,0.937638298148413,-1.44727611258456,0.654266177186554,0.0498015833514871,0.562762750372259,-0.013256420575192,-0.710056197291305,0.0362893828364315,0.301343305201557,1.18037876024002,0.810958518858669,0.0344038243061709,0.817435813435946,-0.473055747424553,0.448777677142348},
    {-0.0908846159775241,-0.758368048499781,-0.805322708258299,-0.7789696193736,0.23503353494938,0.607734906712698,0.225398099596741,-0.0525191501257678,0.73985312550548,0.673372449614874,-0.0490689088995124,0.0894792514197638,-0.998866878141702,-0.859758542888764,-0.928038017135655,-0.506030095255299},
    {-0.763684487859377,0.470704698831836,0.407105018312737,-0.761127671615675,0.00525411171418992,0.736187458269722,-0.353613755105217,-0.932056825680688,-0.0101786169680256,-0.0903460783041563,-0.056082538553481,-0.23277241991145,-0.757001890595414,-0.593714890944993,0.575967595571476,0.958745704995696},
    {0.268836316858878,-0.215241758424273,1.30398428878358,-0.286945322257673,-0.321742825590709,0.703521759060039,0.99117155025474,0.398020257098236,0.266166536116769,-0.411192315213696,0.906168918830044,0.946737992528276,-0.420729160422559,-0.720004323647205,0.0811319322390709,0.104814508665203},
    {0.855332299046876,0.624357208613489,-0.904127873899716,0.236762176890637,-0.0806384004912636,-0.638811536758983,-0.798241318431292,0.508916488379272,-0.12032436389432,-0.794842664316539,0.712107100179208,-0.985751380126794,1.17347475617008,0.0979523186067213,-0.263077846362126,0.192670098127245},
    {0.757280358441161,-1.25664552592384,0.835631722999656,0.497830744356568,1.00556907535554,-2.03378796188495,0.606558737712693,2.62425251473531,0.654325960882697,0.488695498350341,1.54046237876266,-0.515840440754018,1.82022272175222,0.331558781120868,-0.907115835167708,-1.16064232037864}
};

double L2_BIAS[L2_BIAS_COUNT] = {-0.285355805591819,
    0.271500870671329,
    0.0115690038198708,
    0.821318348558945,
    0.544016231002046,
    0.667869413697664,
    -0.173638241206801,
    0.0906926146695117,
    -0.277941438287848,
    0.67552356272145,
    -0.207824199209766,
    -0.260621463666912,
    -0.0938540798497278,
    0.468536324734242,
    0.114559219751653,
    0.0184419409444323
};

double L3_WEIGHTS[L3_WEIGHT_ROW][L3_WEIGHT_COL] = {
    {-0.452567747730925,-2.79915907947352,0.249626437545573,1.0692701627777,-0.2826078197705,-2.39459870137316,0.261933762475794,-0.10525480011121,-1.68486498278658,-2.05899315879435,1.25494948572337,0.957206432443479,-1.43737127176013,-0.882228398172654,0.481990374163908,-3.53410625780755},
    {0.229086514695851,2.20801902446852,0.788912277659577,-0.921148120962398,0.589541463812699,-0.256020531342615,-0.819926025009314,1.21302407736733,0.31809784483041,-0.612038658069901,-1.23861116534606,-0.3610496068149,0.41242918530447,1.13983031791972,-1.17740419937123,2.00566041671414},
    {1.52399650564004,1.47033063845408,0.427984881344033,1.14449340356773,0.606278639979359,2.09629616553491,-0.402276420113305,-0.657046124323765,0.950507980789749,1.69721714943377,-0.226580480058207,-0.806439229748239,-0.150432673637424,0.464893197908041,0.213934303186166,1.37797307177629}
};

double L3_BIAS[L3_BIAS_COUNT] = {-0.0314707235439303, 0.605064426845519, 0.0390738876578246};

void Layer1(double *input_value, double *L1_OUTPUT);
void Layer2(double *L1_OUTPUT, double *L2_OUTPUT);
void Layer3(double *L2_OUTPUT,double *L3_OUTPUT);

void predict(double x, double y, double z);
double relu(double value);
void softmax(double *matrix, int elem);
double softmax_unit(double value, double exponent_sum_of_all);

int main(){
    // double input_values[3] = {-1733.0, 361.0, 3898.0};
    // predict(1,5,4180);
    predict(-3,0,4172);
}

void predict(double x, double y, double z){
    double input_values[3] = {x,y,z};

    double L1_OUTPUT[L1_LAYER];
    double L2_OUTPUT[L2_LAYER];
    double L3_OUTPUT[L3_LAYER];
    double NN_OUTPUT[L3_LAYER];

    Layer1(input_values, L1_OUTPUT);
    for(int i = 0;i < L1_LAYER;i++){printf("%f\n",L1_OUTPUT[i]);}
    printf("\n");

    Layer2(L1_OUTPUT, L2_OUTPUT);
    for(int i = 0;i < L2_LAYER;i++){printf("%f\n",L2_OUTPUT[i]);}
    printf("\n");

    Layer3(L2_OUTPUT,L3_OUTPUT);
    for(int i = 0;i < L3_LAYER;i++){printf("%f\n",L3_OUTPUT[i]);}
    printf("\n");
}

void Layer1(double *input_value, double *L1_OUTPUT){
    double temp;
    for(int i = 0;i < L1_WEIGHT_ROW;i++){
        temp = (input_value[0] * L1_WEIGHTS[i][0]) + (input_value[1] * L1_WEIGHTS[i][1]) + (input_value[2] * L1_WEIGHTS[i][2]) + L1_BIAS[i];
        L1_OUTPUT[i] = relu(temp);
    }
}
//Deb is the best!!!!! :)
void Layer2(double *L1_OUTPUT, double *L2_OUTPUT){
    double temp;
    for(int i = 0;i < L2_WEIGHT_ROW;i++){
        temp = 0;
        for(int j = 0; j < L2_WEIGHT_COL;j++){
            temp = temp + (L1_OUTPUT[j] * L2_WEIGHTS[i][j]);
        }
        temp = temp + L2_BIAS[i];
        L2_OUTPUT[i] = relu(temp);
    }
}
void Layer3(double *L2_OUTPUT,double *L3_OUTPUT){
    double temp;
    for(int i = 0;i < L3_WEIGHT_ROW;i++){
        temp = 0;
        for(int j = 0; j < L3_WEIGHT_COL;j++){
            temp = temp + (L2_OUTPUT[j] * L3_WEIGHTS[i][j]);
        }
        temp = temp + L3_BIAS[i];
        L3_OUTPUT[i] = relu(temp);
    }
    for(int i = 0;i < L3_LAYER;i++){printf("%f\n",L3_OUTPUT[i]);}
    printf("\n");
    softmax(L3_OUTPUT, L3_LAYER);
}

double relu(double value){
    if (value > 0){
        return value;
    }
    else{
        return 0;
    }
}

void softmax(double *matrix, int elem){
    double exponent_sum_all = 0;
    for(int i = 0; i < elem; i++){
        exponent_sum_all += softmax_unit(matrix[i], 1);
    }
    for(int i = 0; i < elem; i++){
        matrix[i] = softmax_unit(matrix[i], exponent_sum_all);
    }
}

double softmax_unit(double value, double exponent_sum_of_all){
    double e = 2.71828;
    double result = pow(e,value) / exponent_sum_of_all;
    return result;
}