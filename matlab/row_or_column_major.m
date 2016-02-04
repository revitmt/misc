clc;
clear all;


loops = 5000;

sizes = 10:30:1000;
difference = size(sizes);


for k = 1:length(sizes)
    n = sizes(k);
    fprintf('size = %i \n',n);

    A = zeros(n,n);
    
    a = rand(n,1);
    tic 
    for j = 1:loops
        for i = 1:n
            A(:,i) = a;
        end
    end
    time1 = toc;
    
    a = rand(1,n);
    tic 
    for j = 1:loops
        for i = 1:n
            A(i,:) = a;
        end
    end
    time2 = toc;
    
    difference(k) = time2 / time1;
    
end

plot(sizes,difference);
title('Column operations / Row operations');
xlabel('Size of matrix');