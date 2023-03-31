%% Load nn
load('my_model.mat')

%% Playground
% x = [-1733.0;361.0;3898.0];
x = [-3;0;4172];
predictions = net(x)
