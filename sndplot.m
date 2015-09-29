function sndplot(l, format)
%SNDPLOT Plot the wave function(s) of a given signal. 
% 
% -- Function File: sndplot (DATA)
% -- Function File: sndplot (DATA, FORMAT)
%
%     This function makes a different plot for each channel
%     of the input. All channels are stacked vertically. 
%
%     The matrix DATA contain the signals to plot, i.e., 
%     the channels of the audio file. 
%
%     The optional parameter FORMAT contains optional plot
%     specifications. 

channels = size(l, 1);

for i = 1 : channels
    subplot (channels, 1, i);
    if exist('format', 'var')
      plot (l(i,:), format);
    else
      plot(l(i,:));
    end	  
end

end
