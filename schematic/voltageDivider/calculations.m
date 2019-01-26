% resistance
R1_nom = 5600;
R2_nom = 8200;
R_relTol = 0.05;
R1_max = R1_nom * (1+R_relTol);
R1_min = R1_nom * (1-R_relTol);
R2_max = R2_nom * (1+R_relTol);
R2_min = R2_nom * (1-R_relTol);

% supply voltage
Vcc_leonardo_nom = 5;
Vcc_leonardo_absTol = 0.05;
Vcc_upBoard_nom = 3.3;
Vcc_upBoard_absTol = 0.1; %just a guess as there is no more information
Vcc_upBoard_min = Vcc_upBoard_nom - Vcc_upBoard_absTol;

% gpio voltage levels
V_OH_max_arduino = Vcc_leonardo_nom + Vcc_leonardo_absTol;
V_OH_min_arduino = 4.2 - Vcc_leonardo_absTol;
V_OL_max_arduino = 0.7 + Vcc_leonardo_absTol;
V_IH_min_upBoard = 2.0; % see: 74LVC1T45
V_IL_max_upBoard = 0.8; % see: 74LVC1T45


%max input high voltage @ upBoard
V_IH_max_upBoard_converted = V_OH_max_arduino / (R1_min + R2_max) * R2_max;
if V_IH_max_upBoard_converted > Vcc_upBoard_min
  error('up board may get too much input voltage!');
else
  disp('maximum input voltage to up board is ok.');
end

%min input high voltage @ upBoard
V_IH_min_upBoard_converted = V_OH_min_arduino / (R1_max + R2_min) * R2_min
if V_IH_min_upBoard_converted < V_IH_min_upBoard
  error('up board may get a too low high level voltage!');
else
  disp('minimal high level input voltage to up board is ok.');
end

%max input low voltage @ upBoard
V_IL_max_upBoard_converted = V_OL_max_arduino / (R1_min + R2_max) * R2_max
if V_IL_max_upBoard_converted > V_IL_max_upBoard
  error('up board may get a too high low level voltage!');
else
  disp('maximal low level input voltage to up board is ok.');
end