clear; 
data = textread('iris.txt');

% plotting original dataset 
scatter3(data(:,2), data(:,3), data(:,4), 20, data(:,1),'filled');
xlabel('1st Feature : x')
ylabel('2nd Feature : z')
zlabel('3rd Feature : w')
title('dataset')

hold on
% covariance.txt로 부터, 
eigen_value_1 = 0.695255;
eigen_vector_1 = [-0.741017;  0.534449;  0.371413;  0.165259];
eigen_value_2 = 0.0522953;
eigen_vector_2 = [-0.203288;  0.325377; -0.540683; -0.748643];
eigen_value_3 = 0.0342659;
eigen_vector_3 = [-0.627892; -0.651523; -0.390595;  0.169427];
eigen_value_4 = 0.106551;
eigen_vector_4 = [-0.123774; -0.428967;  0.645871; -0.619288];
% mean x_0, y_0, z_0
x_0 = 6.588;
y_0 = 2.974;
z_0 = 5.552;
w_0 = 2.026

x_0 = repmat(x_0,size(eigen_vector_1,1),1);
y_0 = repmat(y_0,size(eigen_vector_2,1),1);
z_0 = repmat(z_0,size(eigen_vector_3,1),1);
w_0 = repmat(w_0,size(eigen_vector_4,1),1);
% quiver3(x,y,z,u,v,w): 점 (x,y,z)에 성분 (u,v,w)의 벡터를 표시
quiver3(y_0, z_0, w_0, eigen_vector_2*(eigen_value_2),eigen_vector_3*(eigen_value_3),eigen_vector_4*(eigen_value_4), '-r','LineWidth',5);
hold off

