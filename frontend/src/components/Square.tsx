import React from 'react';

const Square = ({
  dark,
  children
}: {
  dark: boolean;
  children: JSX.Element | null;
}) => {
  const backgroundColor = dark ? 'brown' : 'white';
  const textColor = dark ? 'white' : 'black';
  return (
    <div
      style={{
        backgroundColor,
        color: textColor,
        width: '100%',
        height: '100%'
      }}
    >
      {children}
    </div>
  );
};

export { Square };
