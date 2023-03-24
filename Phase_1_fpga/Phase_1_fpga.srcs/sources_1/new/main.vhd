----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 27.11.2022 09:18:39
-- Design Name: 
-- Module Name: main - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;
library work;
use work.configuration_pack.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity main is
    Port (  a_num0_in: in std_logic_vector(1 downto 0);-- MCU signal and ready pins
            a_num0_out: out std_logic_vector(1 downto 0); -- FPGA data output pins
            a_num1_out: out std_logic_vector(1 downto 0);-- FPGA signal and ready pins
            b_num0: in std_logic_vector(3 downto 0); -- MCU data LSB pins
            b_num1: in std_logic_vector(3 downto 0);-- MCU data MSB pins

            CLK: in std_logic; -- Clock Signal
            S:out std_logic_vector(6 downto 0);-- Seven segment data signal
            an: out std_logic_vector(3 downto 0) --Seven segment anode signal
            );
end main;

architecture Behavioral of main is

    Component output_comparator is
        Port ( 
           clk: in std_logic;
           layer_6_out_array: in layer_6_out;
           result: out std_logic_vector(1 downto 0)
        );
    end Component;

    Component weight_store is
        Port ( 
           mmsu_1_weight_matrix: out layer_1_w;
           mmsu_1_bias_vector: out layer_1_b;
           mmsu_3_weight_matrix: out layer_3_w;
           mmsu_3_bias_vector: out layer_3_b;
           mmsu_5_weight_matrix: out layer_5_w;
           mmsu_5_bias_vector: out layer_5_b
        );
    end Component;

    component rounding_bits_generator is
        Port ( 
          clk: in std_logic;
          random_rounding_bits: out rounding_bits;
          done: out std_logic
        );
      end component;
      
    component MMSU_1 is
        Port ( 
            weight_matrix : in layer_1_w;
            input_vector : in layer_1_in;
            bias_vector: in layer_1_b;
            reset: in std_logic;
            clk: in std_logic;
            random_rounding_bits: in rounding_bits;
            done: out std_logic;
            result : out layer_1_out
        );
    end component;
    
    component VRELU_2 is
        Port ( 
            input: in layer_2_in;
            reset: in std_logic;
            clk: in std_logic;
            done: out std_logic;
            result: out layer_2_out
        );
    end component;
    
    component MMSU_3 is
        Port ( 
            weight_matrix : in layer_3_w;
            input_vector : in layer_3_in;
            bias_vector: in layer_3_b;
            reset: in std_logic;
            clk: in std_logic;
            random_rounding_bits: in rounding_bits;
            done: out std_logic;
            result : out layer_3_out
        );
    end component;
    
    component VRELU_4 is
        Port ( 
            input: in layer_4_in;
            reset: in std_logic;
            clk: in std_logic;
            done: out std_logic;
            result: out layer_4_out
        );
    end component;
    
    component MMSU_5 is
        Port ( 
            weight_matrix : in layer_5_w;
            input_vector : in layer_5_in;
            bias_vector: in layer_5_b;
            reset: in std_logic;
            clk: in std_logic;
            random_rounding_bits: in rounding_bits;
            done: out std_logic;
            result : out layer_5_out
        );
    end component;
    
    component VRELU_6 is
        Port ( 
            input: in layer_6_in;
            reset: in std_logic;
            clk: in std_logic;
            done: out std_logic;
            result: out layer_6_out
        );
    end component;
    
component communication_module is
    port(
        clk : in std_logic;
        mcu_data : in std_logic_vector(7 downto 0);
        mcu_signal : in std_logic;
        mcu_ready : in std_logic;

        fpga_signal : out std_logic;
        fpga_data : out std_logic_vector(1 downto 0);
        fpga_ready : out std_logic;

        input_1_data : out std_logic_vector(15 downto 0);
        input_2_data : out std_logic_vector(15 downto 0);
        input_3_data : out std_logic_vector(15 downto 0);

        nn_out_data : in std_logic_vector(1 downto 0);
        nn_done : in std_logic;
        input_count : out std_logic_vector(2 downto 0)
    );
end component;

Component binto7seg
 Port (Din: in std_logic_vector(3 downto 0);
        Dout:out std_logic_vector(6 downto 0));
end Component;

Component clockdelay
    Port (CLK:in std_logic;
          osCLK:out std_logic);
end Component;


signal segval,seg0,seg1:std_logic_vector(6 downto 0);
signal dispCLK:std_logic;
signal count: std_logic_vector(2 downto 0);

-- Complete input data from MCU
signal input_1_signal: std_logic_vector(15 downto 0);
signal input_2_signal: std_logic_vector(15 downto 0);
signal input_3_signal: std_logic_vector(15 downto 0);

-- MCU status and data pins
signal mcu_signal_signal: std_logic;
signal mcu_ready_signal: std_logic;
signal mcu_data_signal: std_logic_vector(7 downto 0); -- MCU data buffer register

-- Data from NN hardware
signal nn_result_signal: std_logic_vector(1 downto 0); -- Result of inference
signal nn_done_signal: std_logic := '0'; -- Inference completion signal
signal nn_done_clear_signal :std_logic := '0';

--FPGA status and data pins
signal fpga_signal_signal: std_logic;
signal fpga_ready_signal: std_logic;
signal fpga_data_signal: std_logic_vector(1 downto 0); --fpga output data buffer

-- 7 seg display signals
signal din_signal: std_logic_vector(3 downto 0);
signal din_count_signal: std_logic_vector(3 downto 0);
signal counter : std_logic_vector(1 downto 0) := "00";

-- NN signals
signal random_rounding_bits: rounding_bits;
signal generator_done: std_logic;
signal layer_0_output: layer_0_out;

signal mmsu_1_weight_matrix: layer_1_w;
signal mmsu_1_bias_vector: layer_1_b;
signal layer_1_reset: std_logic;
signal layer_1_done: std_logic := '0';
signal layer_1_output: layer_1_out; 

signal layer_2_output: layer_2_out;
signal layer_2_reset, layer_2_done: std_logic;

signal mmsu_3_weight_matrix: layer_3_w;
signal mmsu_3_bias_vector: layer_3_b;
signal layer_3_reset: std_logic := '0';
signal layer_3_done: std_logic := '0';
signal layer_3_output: layer_3_out;

signal layer_4_output: layer_4_out;
signal layer_4_reset, layer_4_done: std_logic;

signal mmsu_5_weight_matrix: layer_5_w;
signal mmsu_5_bias_vector: layer_5_b;
signal layer_5_reset: std_logic := '0';
signal layer_5_done: std_logic := '0';
signal layer_5_output: layer_5_out;

signal layer_6_output: layer_6_out;
signal layer_6_reset, layer_6_done: std_logic;

begin

    -- NN
    layer_1_reset <= fpga_ready_signal;
    layer_2_reset <= not(layer_1_done);
    layer_3_reset <= not(layer_2_done);
    layer_4_reset <= not(layer_3_done);
    layer_5_reset <= not(layer_4_done);
    layer_6_reset <= not(layer_5_done);

    layer_0_output <= (input_1_signal, input_2_signal, input_3_signal);
    nn_done_signal <= layer_6_done;

    -- Communication
    mcu_signal_signal <= a_num0_in(0);
    mcu_ready_signal <= a_num0_in(1);
    mcu_data_signal <= b_num1(3) & b_num1(2) & b_num1(1) & b_num1(0) & b_num0(3) & b_num0(2) & b_num0(1) & b_num0(0);
    
    a_num1_out(0) <= fpga_signal_signal;
    a_num1_out(1) <= fpga_ready_signal;
    a_num0_out <= fpga_data_signal;
    
    din_signal <= b_num0(3) & b_num0(2) & b_num0(1) & b_num0(0);
    din_count_signal <= '0' & count;
    
    comms: communication_module port map(    clk=>clk,
                                        mcu_data=>mcu_data_signal,
                                        mcu_signal=>mcu_signal_signal,
                                        mcu_ready=>mcu_ready_signal,

                                        fpga_signal=>fpga_signal_signal,
                                        fpga_data=>fpga_data_signal,
                                        fpga_ready=>fpga_ready_signal,
                                        
                                        input_1_data=>input_1_signal,
                                        input_2_data=>input_2_signal,
                                        input_3_data=>input_3_signal,

                                        nn_done=>nn_done_signal,
                                        nn_out_data=>nn_result_signal,
                                        input_count => count
                                    );

    WEIGHTS: weight_store port map( mmsu_1_weight_matrix => mmsu_1_weight_matrix,
                                    mmsu_1_bias_vector => mmsu_1_bias_vector,
                                    mmsu_3_weight_matrix => mmsu_3_weight_matrix,
                                    mmsu_3_bias_vector => mmsu_3_bias_vector,
                                    mmsu_5_weight_matrix => mmsu_5_weight_matrix,
                                    mmsu_5_bias_vector => mmsu_5_bias_vector);

    GENERATOR: rounding_bits_generator port map(clk => clk, random_rounding_bits => random_rounding_bits, done => generator_done);

    LAYER_MMSU_1: MMSU_1 port map(weight_matrix => mmsu_1_weight_matrix, input_vector => layer_0_output, 
                         bias_vector => mmsu_1_bias_vector, reset => layer_1_reset, clk => clk, 
                         random_rounding_bits => random_rounding_bits, done => layer_1_done, 
                         result => layer_1_output);
                         
    LAYER_VRELU_2: VRELU_2 port map(input => layer_1_output, reset => layer_2_reset, clk => clk, 
                                     done => layer_2_done, result => layer_2_output);
                                     
    LAYER_MMSU_3: MMSU_3 port map(weight_matrix => mmsu_3_weight_matrix, input_vector => layer_2_output, 
                         bias_vector => mmsu_3_bias_vector, reset => layer_3_reset, clk => clk, 
                         random_rounding_bits => random_rounding_bits, done => layer_3_done, 
                         result => layer_3_output);
                         
    LAYER_VRELU_4: VRELU_4 port map(input => layer_3_output, reset => layer_4_reset, clk => clk, 
                                     done => layer_4_done, result => layer_4_output);
                                     
    LAYER_MMSU_5: MMSU_5 port map(weight_matrix => mmsu_5_weight_matrix, input_vector => layer_4_output, 
                         bias_vector => mmsu_5_bias_vector, reset => layer_5_reset, clk => clk, 
                         random_rounding_bits => random_rounding_bits, done => layer_5_done, 
                         result => layer_5_output);
                         
    LAYER_VRELU_6: VRELU_6 port map(input => layer_5_output, reset => layer_6_reset, clk => clk, 
                                     done => layer_6_done, result => layer_6_output);

    SOFTMAX: output_comparator port map(clk=>clk,layer_6_out_array => layer_6_output, result => nn_result_signal);

    -- Display on 7 seg
    conv1: binto7seg port map(Din=>din_signal, Dout=>seg0); 
    conv2: binto7seg port map(Din=>din_count_signal, Dout=>seg1);
    clkctrl: clockdelay port map(CLK=>CLK, osCLK=>dispCLK);
    
    process(dispCLK)
    begin
        if(rising_edge(dispCLK)) then
            counter <= counter + 1;
        end if;
    end process;
    
--    with countert select 
with counter select
    S <= not(seg0) when "00",
         not(seg0) when "01",
         not(seg1) when "10",
         not(seg1) when others;
            
with counter select
   an<= "1101" when "00",
        "1101" when "01",
        "1110" when "10",
        "1110" when others;

end Behavioral;
