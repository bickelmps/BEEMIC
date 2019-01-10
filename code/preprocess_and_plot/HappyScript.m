%%
cd 'C:\Users\Omanovic\Desktop\PolyHack\json files\Happy\Front'

filelist = dir('C:\Users\Omanovic\Desktop\PolyHack\json files\Happy\Front');

for ii = 3:length(filelist)-1
    filename = filelist(ii).name;
    data(ii-2) = jsondecode(fileread(filename));
end

for ii = 1:length(data)
    yValues(ii) = data(ii).people.pose_keypoints(4);
    zValues(ii) = data(ii).people.pose_keypoints(5);
end
%%
cd 'C:\Users\Omanovic\Desktop\PolyHack\json files\Happy\Side'

filelist = dir('C:\Users\Omanovic\Desktop\PolyHack\json files\Happy\Side');

for ii = 3:length(filelist)-1
    filename = filelist(ii).name;
    data(ii-2) = jsondecode(fileread(filename));
end

for ii = 1:length(data)
    xValues(ii) = data(ii).people.pose_keypoints(4);
end

%%

xValuesNorm_Happy = xValues - mean(xValues);
yValuesNorm_Happy = yValues - mean(yValues);
zValuesNorm_Happy = zValues - mean(zValues);

%%
% plot(xValuesNorm_Happy)
% hold on
% plot(yValuesNorm_Happy)
% plot(zValuesNorm_Happy)