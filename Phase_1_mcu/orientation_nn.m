%% Load Training Data
fb_data_table = readtable('labeled_forward_back.csv');
ud_data_table = readtable('labeled_up_down.csv');
still_data_table = readtable('labeled_still.csv');

%% Format training data
fb_data = table2array(fb_data_table);
ud_data = table2array(ud_data_table);
still_data = table2array(still_data_table);
all_data = vertcat(fb_data, vertcat(ud_data, still_data));
all_data = all_data(randperm(size(all_data, 1)), :);
%% Split data
x = all_data(:,1:3);
y = all_data(:,4:4);

%% Orient data
x = transpose(x);
y = transpose(y);

%% Encode output
categories = y;
numCategories = 3;
encoded_y = zeros(numCategories,length(categories));

% Loop over each category and encode it as a binary vector
for i = 1:length(categories)
    val = categories(:,i);
    encoded_y(categories(:,i)+1, i) = 1;
end
%% Neural Network Architecture
hiddenLayers = [16 16];
net = patternnet(hiddenLayers);
net.layers{1}.transferFcn = 'poslin';
net.layers{2}.transferFcn = 'poslin';
view(net)

%% Training
[net,tr] = train(net,x,encoded_y);
save("model.mat");

%% Load Model
load('my_model.mat')
%% Post Training
i_l1_weights = net.IW{1};
i_l1_bias = net.b{1};

l1_l2_weights = net.LW{2,1};
l1_l2_bias = net.b{2};
l2_o_weights = net.LW{3,2};
l2_o_bias = net.b{3};

size(i_l1_weights)
% size(i_l1_bias)

size(l1_l2_weights)
% size(l1_l2_bias)

size(l2_o_weights)
% size(l2_o_bias)


%% Exporting weights and biases
writematrix(l1_l2_weights,'l1_l2_weights.csv');
writematrix(l1_l2_bias,'l1_l2_bias.csv');

writematrix(i_l1_weights,'i_l1_weights.csv');
writematrix(i_l1_bias,'i_l1_bias.csv');

writematrix(l2_o_weights,'l2_o_weights.csv');
writematrix(l2_o_bias,'l2_o_bias.csv');

