%% Compare all figures

% Run all scripts
clear
run HappyScript.m
cd 'C:\Users\Omanovic\Desktop\PolyHack\json files'
HappyData.xValues = xValuesNorm_Happy;
HappyData.xValues(115:end) = -12.8;
HappyData.yValues = yValuesNorm_Happy;
for ii = 1:length(HappyData.yValues)
    HappyData.yValues(ii) = HappyData.yValues(ii) + ii/length(HappyData.yValues) * (HappyData.yValues(1)-HappyData.yValues(end));
end
HappyData.zValues = zValuesNorm_Happy;
save('HappyData.mat','HappyData');
clear
run LostScript.m
cd 'C:\Users\Omanovic\Desktop\PolyHack\json files'
LostData.xValues = xValuesNorm_Lost;
LostData.xValues(140:end) = -5.8;
LostData.yValues = yValuesNorm_Lost;
LostData.zValues = zValuesNorm_Lost;
LostData.zValues(160:end) = -2.7; 
save('LostData.mat','LostData');
clear
run SneakScript.m
cd 'C:\Users\Omanovic\Desktop\PolyHack\json files'
SneakData.xValues = xValuesNorm_Sneak;
for ii = 138:length(SneakData.xValues)
    SneakData.xValues(ii) = 47.17 - (ii-138)*(47.17-20)/length((138:length(SneakData.xValues)));
end
SneakData.yValues = yValuesNorm_Sneak;
SneakData.zValues = zValuesNorm_Sneak;
SneakData.zValues(160:end) = -14.7;
save('SneakData.mat','SneakData');
clear

%%

load('HappyData.mat');
load('LostData.mat');
load('SneakData.mat');

figure(11)

subplot(1,3,1)
plot(HappyData.xValues, 'k','LineWidth',2);
hold on
plot(HappyData.yValues, 'b','LineWidth',2);
plot(HappyData.zValues, 'r','LineWidth',2);
for ii = 1:20
    plot(ii*6, HappyData.xValues(ii*6), 'g*')
    plot(ii*6, HappyData.yValues(ii*6), 'g*')
    plot(ii*6, HappyData.zValues(ii*6), 'g*')
end
legend('Vorwärts','Seitlich','Höhe');
title('Happy Jump');

subplot(1,3,2)
plot(LostData.xValues, 'k','LineWidth',2);
hold on
plot(LostData.yValues, 'b','LineWidth',2);
plot(LostData.zValues, 'r','LineWidth',2);
for ii = 1:30
    plot(ii*6, LostData.xValues(ii*6), 'g*')
    plot(ii*6, LostData.yValues(ii*6), 'g*')
    plot(ii*6, LostData.zValues(ii*6), 'g*')
end
legend('Vorwärts','Seitlich','Höhe');
title('Lost')

subplot(1,3,3)
plot(SneakData.xValues, 'k','LineWidth',2);
hold on
plot(SneakData.yValues, 'b','LineWidth',2);
plot(SneakData.zValues, 'r','LineWidth',2);
for ii = 1:27
    plot(ii*6, SneakData.xValues(ii*6), 'g*')
    plot(ii*6, SneakData.yValues(ii*6), 'g*')
    plot(ii*6, SneakData.zValues(ii*6), 'g*')
end
legend('Vorwärts','Seitlich','Höhe');
title('Sneaky man')

%%

Happy(:,1) = HappyData.xValues;
Happy(:,2) = HappyData.yValues;
Happy(:,3) = HappyData.zValues;

Lost(:,1) = LostData.xValues;
Lost(:,2) = LostData.yValues;
Lost(:,3) = LostData.zValues;

Sneak(:,1) = SneakData.xValues;
Sneak(:,2) = SneakData.yValues;
Sneak(:,3) = SneakData.zValues;

%%
plot3(OriginalResult(:,1),OriginalResult(:,2),OriginalResult(:,3))
hold on
plot3(smooth(HappyResult(:,1)),smooth(HappyResult(:,2)),smooth(HappyResult(:,3)),'LineWidth',2)
plot3(smooth(LostResult(:,1)),smooth(LostResult(:,2)),smooth(LostResult(:,3)),'LineWidth',2)
plot3(smooth(SneakResult(:,1)),smooth(SneakResult(:,2)),smooth(SneakResult(:,3)),'LineWidth',2)
ylim([-2 2])
legend('ideal','Happy','Lost','Sneak')

