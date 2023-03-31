%% Get Data
[x,t] = bodyfat_dataset;
size(x)
size(t)

%% Architecture
hiddenLayers = [5];
net = fitnet(hiddenLayers);
% net.layers{1}.transferFcn = 'poslin';
% net.layers{2}.transferFcn = 'poslin';
view(net)

%% Train
[net,tr] = train(net,x,t);

%% Evaluation