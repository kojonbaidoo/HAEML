%% Load model
load('my_model.mat')

%% Separation
i_l1_weights = net.IW{1};
i_l1_bias = net.b{1};

l1_l2_weights = net.LW{2,1};
l1_l2_bias = net.b{2};
l2_o_weights = net.LW{3,2};
l2_o_bias = net.b{3};

%% Conversion to fixed point
% Define the floating-point number
float_0 = i_l1_weights;
float_1 = i_l1_bias;

float_2 = l1_l2_weights;
float_3 = l1_l2_bias;

float_4 = l2_o_weights;
float_5 = l2_o_bias;

file_names = [  'fixed_i_l1_weights.txt','fixed_i_l1_bias.txt',...
                'fixed_l1_l2_weights.txt','fixed_l1_l2_bias.txt',...
                'fixed_l2_o_weights.txt','fixed_l2_lo_bias.txt'];

weights_0 = sfi(float_0,16,8);
weights_0 = weights_0.bin;
t = table(weights_0);
writetable(t,'fixed_i_l1_weights.txt')

bias_0 = sfi(float_1,16,8);
bias_0 = bias_0.bin;
t = table(bias_0);
writetable(t,'fixed_i_l1_bias.txt')

weights_1 = sfi(float_2,16,8);
weights_1 = weights_1.bin;
t = table(weights_1);
writetable(t,'fixed_l1_l2_weights.txt')

bias_1 = sfi(float_3,16,8);
bias_1 = bias_1.bin;
t = table(bias_1);
writetable(t,'fixed_l1_l2_bias.txt')

weights_2 = sfi(float_4,16,8);
weights_2 = weights_2.bin;
t = table(weights_2);
writetable(t,'fixed_l2_o_weights.txt')

bias_2 = sfi(float_5,16,8);
bias_2 = bias_2.bin;
t = table(bias_2);
writetable(t,'fixed_l2_lo_bias.txt')
