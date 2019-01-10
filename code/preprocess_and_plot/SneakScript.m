%%
cd 'C:\Users\Omanovic\Desktop\PolyHack\json files\Sneak\Front'

filelist = dir('C:\Users\Omanovic\Desktop\PolyHack\json files\Sneak\Front');

for ii = 3:length(filelist)-1
    filename = filelist(ii).name;
    data(ii-2) = jsondecode(fileread(filename));
end

for ii = 1:length(data)
    yValues(ii) = data(ii).people.pose_keypoints(4);
    zValues(ii) = data(ii).people.pose_keypoints(5);
end
%%
cd 'C:\Users\Omanovic\Desktop\PolyHack\json files\Sneak\Side'

filelist = dir('C:\Users\Omanovic\Desktop\PolyHack\json files\Sneak\Side');

for ii = 3:length(filelist)-1
    filename = filelist(ii).name;
    data(ii-2) = jsondecode(fileread(filename));
end

for ii = 1:length(data)
    xValues(ii) = data(ii).people.pose_keypoints(4);
end

%%

xValuesNorm_Sneak = xValues - mean(xValues);
yValuesNorm_Sneak = yValues - mean(yValues);
zValuesNorm_Sneak = zValues - mean(zValues);

%%
% plot(xValuesNorm_Sneak)
% hold on
% plot(yValuesNorm_Sneak)
% plot(zValuesNorm_Sneak)