%%
cd 'C:\Users\Omanovic\Desktop\PolyHack\json files\Lost\Front'

filelist = dir('C:\Users\Omanovic\Desktop\PolyHack\json files\Lost\Front');

for ii = 3:length(filelist)-1
    filename = filelist(ii).name;
    data(ii-2) = jsondecode(fileread(filename));
end

for ii = 1:length(data)
    yValues(ii) = data(ii).people.pose_keypoints(4);
    zValues(ii) = data(ii).people.pose_keypoints(5);
end
%%
cd 'C:\Users\Omanovic\Desktop\PolyHack\json files\Lost\Side'

filelist = dir('C:\Users\Omanovic\Desktop\PolyHack\json files\Lost\Side');

for ii = 3:length(filelist)-1
    filename = filelist(ii).name;
    data(ii-2) = jsondecode(fileread(filename));
end

for ii = 1:length(data)
    xValues(ii) = data(ii).people.pose_keypoints(4);
end

%%

xValuesNorm_Lost = xValues - mean(xValues);
yValuesNorm_Lost = yValues - mean(yValues);
zValuesNorm_Lost = zValues - mean(zValues);

%%
% plot(xValuesNorm_Lost)
% hold on
% plot(yValuesNorm_Lost)
% plot(zValuesNorm_Lost)